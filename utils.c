#include "utils.h"

unsigned int absu(int value) {
    return (value < 0) ? -((unsigned int)value) : (unsigned int)value;
}

unsigned int maxu(unsigned int a, unsigned int b) {
    return (a > b) ? a : b;
}

int digitCount(unsigned int value) {
    return (int)(log10(value)) + 1;
}

char getChar() {
    // Disables the COOKED mode of the terminal
    char            key = 0;        // Stores keystrokes in ASCII
    struct termios  old = {0};      // Current terminal settings

    if (tcgetattr(0, &old) < 0)     // Read current attributes
        perror("tcsetattr()");

    // Update them

    // Local modes
    old.c_lflag &= ~ICANON;         // Enable canonical mode
    old.c_lflag &= ~ECHO;           // Echo input characters
    // Special characters
    old.c_cc[VMIN] = 1;             // Minimum number of characters for read
    old.c_cc[VTIME] = 0;            // Timeout for read

    // Store changes

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    // Record a single key stroke
    if (read(0, &key, 1) < 0)
        perror("read()");

    // Revert back

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    
    return key;
}
