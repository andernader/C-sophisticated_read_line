//The aim and the goal is to create a read input function, that reads string
//user input, where this function is robust and can be used in my future pr-
//ojects without any problem.
//The main points I want from this function and her sisters:
//1. Handle empty input(only '\n')
//2. Handle EOF(only EOF)
//3. Handle Buffer range.
//4. Being able to remove leading and trailing whitespace.
//5. Being able to show default Error messages, and the ability to turn them off.
//6. Being able to loop and ask for user input again if the line is empty or needed to ask for that.
//
//For now:
//1. Function to take user input directly.
//2. Function to take input from different input streams. LATER
//3. Function to take input from a string literal. LATER

#ifndef READLINE_H
#define READLINE_H

//We have multiple variables included in readline.c that control the behavior of the function.
extern int READLINE_MSG;
extern int READLINE_LOOP;
extern int READLINE_SPACE_LEAD;
extern int READLINE_SPACE_TRAIL;

#define ERROR_EOF "Error: No input received (EOF encountered)."
#define ERROR_EMPTY "Error: Empty input!"
#define ERROR_OVERFLOW "Error: Buffer overflow!"
#define ERROR_SPACE "Error: The line is full of only space! Can't remove the space!"

void printerr(char msg[]);
void empty_input_buffer(void);
int remove_leading_space(char line[], int length);
int remove_trailing_space(char line[], int length);
int read_line(char line[], int length);

#endif // READLINE_H
