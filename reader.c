#include "reader.h"

void printer(int value) {
    // Move the cursor back
    int digits = digitCount(absu(value)), i;
    for (i = 0; i < digits; i++)
        printf("\b");    

    // Color and display the value
    if (value < 0)
        printf(CRED "%d" CREG, value);
    else if (value == 0)
        printf(CREG "\b %d\b" CREG, value);
    else
        printf(" " CGRE "%d" CREG, value);

    // Do not wait for EOL to flush to terminal
    fflush(stdout);
}

int readInt(int *destination, int intMin, int intMax) {
    // readInt() reads a single integer from stdin buffer
    // If successful it will
    // - store read result to the destination address
    // - return 0
    // Otherwise it will not alter destination and return the error number
    // 1 - value has not been assigned

    unsigned char   error = 1;           // Initiate with the no value error - 1

    char            got,                 // Temporary storage for each getChar()
                    flagNegative    = 0; // Default 0 = positive

    int             value           = 0, // As long as (error != 0), this is disregarded
                    valueAbs        = 0,
                    digit           = 0,
                    digitAdjusted   = 0,
                    digits = digitCount(maxu(absu(intMin), absu(intMax))),
                    digitLastIntMin = intMin - (intMin/10)*10,
                    digitLastIntMax = intMax - (intMax/10)*10;

    // Tests
    int     maxReached,             // Max value reached
            maxDivTenExceeded,      // Max value would be exceeded by any digit
            maxLastDigitExceeded,   // Max value is exceeded one digit upwards
            minReached,
            minDivTenExceeded,
            minLastDigitExceeded,
            stopMax,                // All max tests combined
            stopMin,
            growth;

    // Draw placeholders for the number
    char    placeholder = '_';
    int     i;

    printf(" ");                    // Place for the sign
    for (i = 0; i < digits; i++)    // _ <- placeholder
        printf("%c", placeholder);
    for (i = 0; i < digits; i++)    // Return cursor to the start of the line
        printf("\b");
    fflush(stdout);

    while (1) {
        // Record key strokes into an int
        got = getChar();

        // Check if it is one of the accepted values:
        // 45 = '-'
        // 48 = '0'
        // ...
        // 57 = '9'
        //
        // Terminate reading when encountered a new line or reached MAX_INT
        // 10 = '\n'
        //
        // Modify the value if:
        // 127 or '\b' = backspace

        if ((got == 45) || ((got >= 48) && (got <= 57))) {
            // Valid
            if (!(got == 45)) {
                digit = got - 48;
                digitAdjusted = (flagNegative) ? -digit : digit;
                
                // Tests

                // Upper bound
                maxReached              = (value == intMax) && (intMax != 0);
                maxDivTenExceeded       = value > (intMax/10);
                maxLastDigitExceeded    = (value == (intMax/10)) && (digitAdjusted > digitLastIntMax);
                // Lower bound
                minReached              = (value == intMin) && (intMin != 0);
                minDivTenExceeded       = value < (intMin/10);
                minLastDigitExceeded    = (value == (intMin/10)) && (digitAdjusted < digitLastIntMin);
                // Stop conditions
                stopMax                 = maxReached || maxDivTenExceeded || maxLastDigitExceeded;
                stopMin                 = minReached || minDivTenExceeded || minLastDigitExceeded;
                // Value moving in the right direction (even if not there yet)
                growth = (((intMin > 0) && (digitAdjusted > 0) && !stopMax) ||
                          ((intMax < 0) && (digitAdjusted < 0) && !stopMin)) ? 1 : 0;

                // Prevent integer overflow
                if ((stopMax || stopMin) && !growth) {
                    //printf("Integer overflow: value=%d; digit=%d\n", value, digit);
                    //fflush(stdout);
                }
                // Good to go - add the digit
                else {
                    if (flagNegative)
                        value = value*10 - digit;
                    else
                        value = value*10 + digit;
                    
                    // If value == 0, remove negative flag
                    if (value == 0)
                        flagNegative = 0;

                    // Since we have a value now, remove the error
                    error = 0;

                    // Save an absolute version too
                    valueAbs = absu(value);

                    // Display the result so far to the user
                    printer(value);

                    // If digit limit reached, don't move the cursor
                    if (digitCount(valueAbs) == digits) {
                        printf("\b");
                        fflush(stdout);
                    }
                }
            } else {
                if ((!value) && (intMin < 0)) {
                    flagNegative = 1; // Save the negative flag
                    printf("\b-%c\b", placeholder);
                    fflush(stdout);
                }
            }
        } else if (got == 10) {
            // '\n' = new line - completes number extraction
            // Only if there is not pending error
            if (!error) {
                // Check if the value is within required bounds
                if (intMin <= value && value <= intMax)
                    break;
            }
        } else if ((got == 127) || (got == '\b')) {
            // backspace - remove the rightmost digit

            // Value is in the multiple digits
            if (valueAbs > (unsigned int)9) {
                if (digitCount(valueAbs) == digits)
                    printf("%c\b\b", placeholder);
                else
                    printf("\b%c\b\b", placeholder);
                fflush(stdout);

                value /= 10;
                valueAbs = absu(value);
                printer(value);
            } 
            // Value is single digit
            else if ((valueAbs <= (unsigned int)9) && (valueAbs > (unsigned int)0)) {
                if (digits == 1)
                    printf("%c\b", placeholder);
                else
                    printf("\b%c%c\b\b", placeholder, placeholder);                
                fflush(stdout);

                value /= 10;
                valueAbs = absu(value);
                
                // We no longer have a value, set the error back on
                error = 1;
            } 
            // Value reached zero
            else {
                printf("\b\b  %c\b", placeholder);
                fflush(stdout);
                
                // Reset the negative flag
                flagNegative = 0;
            }
        } 
        else {
            // Invalid
            //printf("Invalid: %d:%d\n", got, got);
        }
    }

    // If there is no error, send of the value
    if (!error)
        *destination = value;

    //
    // Post formatting inline
    //

    // If the digit limit was reached, the cursor should move right
    int     digitsCounted = digitCount(valueAbs),
            valueLength = (digitsCounted > 0) ? digitsCounted : 0,
            moveForward = (valueLength == digits) ? 1 : (digits - valueLength);

    printf("\x1B[%dC", moveForward);
    fflush(stdout);

    return error;
}

int readIntNoRange(int *destination) {
    return readInt(destination, INT_MIN, INT_MAX);
}

int readIntRangeUpTo(int *destination, int intMax) {
    return readInt(destination, INT_MIN, intMax);
}

int readIntRangeDownTo(int *destination, int intMin) {
    return readInt(destination, intMin, INT_MAX);
}

int readIntReturn() {
    int d;
    readIntNoRange(&d);
    return d;
}
