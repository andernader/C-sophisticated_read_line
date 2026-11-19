#ifndef DEBUG_F_H
#define DEBUG_F_H

#ifdef DEBUG
//Print int value only of a variable in debug mode.
#define PRINT_DEBUG_int(x) printf("%-20s = %d | (int) value only.\n", #x, x)
//print char value and int value of a variable in debug mode.
#define PRINT_DEBUG_char_int(x) printf("%-20s = %c | (char) value.\n%-20s = %d | (int) value.\n\n", #x, x, #x, x)
//print a message in debug mode.
#define PRINT_DEBUG_MSG(x) printf("%s\n", x)
//Print a string var in debug mode.
#define PRINT_DEBUG_STR_VALUE(x) printf("%s = %s\n", #x, x)
//print line, file, function in debug mode.
#define PRINT_DEBUG_LOCATION() printf("\n\nLine: %d | Function: %s | File: %s\n", __LINE__, __func__, __FILE__)
//convert to string in debug mode.
#define STR_DEBUG(x) #x
//print debug arr int
#define PRINT_DEBUG_ARR_int(x, length) printf("%s: \n", #x);for(int i = 0; i < length; i++)printf(" %d", x[i]);putchar('\n')

#endif // DEBUG

#ifndef DEBUG
#define PRINT_DEBUG_int(x)
#define PRINT_DEBUG_char_int(x)
#define PRINT_DEBUG_MSG(x)
#define PRINT_DEBUG_STR_VALUE(x)
#define PRINT_DEBUG_LOCATION(x)
#define STR_DEBUG(x)
#define PRINT_DEBUG_ARR_int(x, length)
#endif // DEBUG

#endif // DEBUG_F_H
