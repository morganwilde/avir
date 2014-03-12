#include "ui.h"

Env envGet() {
    // Get window meta data
    struct winsize terminal;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal);
    // Store it
    Env env;
    env.w = terminal.ws_col;
    env.h = terminal.ws_row;

    return env;
}

char *borderHorizontal() {
    Env env = envGet();
    char *border = malloc(sizeof(char) * env.w);
    int i = 0;

    // Construct border
    border[i] = '+';
    for (i = 1; i < env.w; i++)
        border[i] = '-';
    border[--i] = '+';
    border[++i] = '\0';

    return border;
}

char *borderVertical(char *message) {
    Env     env = envGet();
    char   *border = malloc(sizeof(char) * env.w);
    int     i = 0,
            m = 0,
            left = 0;

    // Calculate the left padding to center message
    left = env.w/2 - strlen(message)/2;

    // Construct border
    border[i] = '|';
    border[++i] = ' ';
    for (i = 2; i < env.w; i++) {
        // Copy the message
        if ((m < strlen(message)) && (i >= left)) {
            border[i] = message[m];
            m++;
        }
        // When the message is complete, just pad it out
        else
            border[i] = ' ';

    }
    border[--i] = '|';
    border[++i] = '\0';

    return border;
}

void printDisplay(char *messages[], int count) {
    int i;
    printf("%s", borderHorizontal());
    
    for (i = 0; i < count; i++)
        printf("%s", borderVertical(messages[i]));

    printf("%s", borderHorizontal());
}
