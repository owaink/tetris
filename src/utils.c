#include <stdlib.h>
#include "utils.h"

void swap(int* x, int* y) {
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}