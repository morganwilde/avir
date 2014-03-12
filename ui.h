#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct Env {
    int     w,  // Will hold the width of the terminal window and the
            h;  // Height
} Env;


Env     envGet();
char   *borderHorizontal();
char   *borderVertical(char *message);
void    printDisplay(char *messages[], int count);
