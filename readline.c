#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "readline.h"
#include "debug_f.h"

int READLINE_MSG = 0; //Show default Error messages, default do not show.
int READLINE_LOOP = 1; //Go for loop if input is invalid and ask for input again, default yes.
int READLINE_SPACE_LEAD = 0; //Remove leading whitespace, default no.
int READLINE_SPACE_TRAIL = 0; //Remove trailing whitespace, default no.

//Print error messages only if READLINE_MSG is 1.
void printerr(char msg[]){
    if(READLINE_MSG == 1)
        fprintf(stderr, "%s\n", msg);
    return;
}

//consume everything on the input buffer.
void empty_input_buffer(void){
    int temp_char;
    while((temp_char = getchar()) != '\n' && temp_char != EOF)
        ;
    return;
}

//Find the first non whitespace character, then remove all whitespace before it.
int remove_leading_space(char line[], int length){
    if(READLINE_SPACE_LEAD == 1){       //If leading space flag is on remove it, otherwise do not.
        int i;
        char temp_line[length];

        for(i = 0; line[i] != '\0' && i < length ; i++)//The range is length, but if you find '\0' break.
            if(isspace((unsigned char)line[i]) == 0){ //go up to the first non white space character in the line.
                break;
        }
        if(i >= length){                //if we did not find any non whitespace character that means the whole line is only whitespace.
            printerr(ERROR_SPACE);
            return -1;
        }
        strcpy(temp_line, &line[i]);
        memset(line, 0, length);
        strcpy(line, temp_line);
        return 0;
    }
    return 0;
}

//Find from the end of the string the first non white space character, and remove everything after it.
int remove_trailing_space(char line[], int length){
    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG_int(READLINE_SPACE_TRAIL);
    PRINT_DEBUG_int(length);
    if(READLINE_SPACE_TRAIL == 1){
        int i;
        for(i = length - 1; i >= 0; i--){  //the range is before the null terminator '\0' up to 0.
            if(isspace((unsigned char)line[i]) == 0)           //stop at the first non white space character.
                break;
        }
        PRINT_DEBUG_int(i);
        if(i < 0){                              //if we have i smaller than 0 that means even the index 0 has space that we skipped.
            printerr(ERROR_SPACE);
            return -1;
        }

        for(++i; i < length; i++)               //Set everything after that letter to '\0' which is byte 0.
            line[i] = '\0';
        PRINT_DEBUG_STR_VALUE(line);
        return 0;
    }
    return 0;
}

//Read user input, return length of the input read, return EOF if faced,
//return 0 if empty line with only '\n'
int read_line(char line[], int length){
    int read_characters = 0;
    int temp_char;
    if(length <= 0)         //if length is 0 or less this is not a valid array!
        return -3;
    char temp_line[length];  //This is a temp line that we will store our input in it before we trim whitespace if needed!
    int flag_overflow = 0;  //Flag for when we have input bigger than the buffer size.

    process:
    while(1){
        temp_char = getchar();
        if(temp_char == EOF && read_characters == 0){   //This situation is EOF, no input before.
            printerr(ERROR_EOF);                        //If faced, print error message, and return.
            return EOF;
        }
        if(temp_char == '\n' && read_characters == 0){  //This situation is empty line where we only have '\n'
            printerr(ERROR_EMPTY);                       //if faced, print error message and ask for input again!
            if(READLINE_LOOP == 1)                      //go again for input if READLINE_LOOP = 1, and don't increase the read_characters!
                continue;
            else
                return -2;                              //if READLINE_LOOP is not active return.
        }
        if(read_characters != 0 && (temp_char == '\n' || temp_char == EOF)){ //if we have EOF or '\n' after reading input
            break;                                  //break because we still wanna check the other functions to adjust the input.
        }
        if(read_characters >= length - 1){          //if read_characters exceed the buffer limit - 1, the -1 is for '\0'
            flag_overflow = 1;                      //if so, set flag to 1, in order to consume the remaining input characters in stdin.
            printerr(ERROR_OVERFLOW);               //print error, and break out to consume leftovers.
            break;
        }
        temp_line[read_characters] = temp_char;     //Store the character.
        read_characters++;                          //Increase the number of the characters read.
    }

    temp_line[read_characters] = '\0';              //terminate the line with null terminator.

    if(flag_overflow == 1)                          //If we have overflow, and overflow only we empty the input buffer.
        empty_input_buffer();

    if(remove_leading_space(temp_line, strlen(temp_line)) == -1 && READLINE_LOOP == 1){ //if we have a line full of space,
        read_characters = 0;                           //reset everything, and start the process again.
        flag_overflow = 0;                             //The error message is shown inside the function.
        memset(temp_line, 0, length);
        goto process;
    }

    if(remove_trailing_space(temp_line, strlen(temp_line)) == -1 && READLINE_LOOP == 1){ //if we have lets say the situation where we are only
        read_characters = 0;                            //removing the trailing white space in a line full of spaces
        flag_overflow = 0;                              //this situation will trigger.
        memset(temp_line, 0, length);
        goto process;
    }

    strcpy(line, temp_line);
    return strlen(line);
}
