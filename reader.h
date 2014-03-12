#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "utils.h"

// Colors

#define CREG "\x1B[0m"
#define CRED "\x1B[31m"
#define CGRE "\x1B[32m"

void printer(int value);

// Read functions

// Designated function
int readInt(int *destination, int intMin, int intMax);
// Secondary functions
int readIntNoRange(int *destination);
int readIntReturn();
int readIntRangeUpTo(int *destination, int intMax);
int readIntRangeDownTo(int *destination, int intMin);
