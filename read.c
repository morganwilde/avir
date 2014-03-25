#include "reader.h"
#include "ui.h"

// TODO - reverse the direction of the numbers, start right most, then move left

int main(int argc, char *argv[]) {

    int     number,
            message;

    // Post a UI
    char *messages[] = {
        "",
        "The always valid integer reader - AVIR.",
        "",
        NULL
    };
    //printDisplay(messages, 3);

    // Display possible interfaces
    
    message = readIntNoRange(&number);
    printf(" ---> [%d]\n", number);
    /*
    printf("(%d; %d) %24s", INT_MIN, INT_MAX, "Type bounded number: ");
    message = readIntNoRange(&number);
    printf(" ---> [%d]\n", number);

    printf("(%d; %d) %40s", 10, 111, "User bounded number: ");
    message = readInt(&number, 10, 111);
    printf("%7s ---> [%d]\n", "",  number);

    printf("(%d; %d) %30s", INT_MIN, 1024, "Upper bound number: ");
    message = readIntRangeUpTo(&number, 1024);
    printf(" ---> [%d]\n",  number);

    printf("(%d; %d) %30s", -1024, INT_MAX, "Lower bound number: ");
    message = readIntRangeDownTo(&number, -1024);
    printf(" ---> [%d]\n\n",  number);
    
    printf("Inline number one: ");
    readIntReturn();
    printf(", and number two: ");
    readIntReturn();
    printf(".\n");
    */

    return 0;
}
