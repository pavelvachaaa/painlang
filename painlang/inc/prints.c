#include <stdio.h>
#include "config.h"

void debug_print(char* to_print)
{
    #ifdef PRINTS_DEBUG
    printf("%s\n", to_print);
    #endif
}
