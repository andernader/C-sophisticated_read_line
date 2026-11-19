#include <stdio.h>
#include "readline.h"
#define MAX_LEN 20

int main(void){
    char line[MAX_LEN + 1];

    READLINE_LOOP = 1;
    READLINE_MSG = 0;
    READLINE_SPACE_LEAD = 1;
    READLINE_SPACE_TRAIL = 1;

    read_line(line, MAX_LEN + 1);
    printf("%s.\n\n", line);

    return 0;
}
