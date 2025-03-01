#include <stdio.h>
#include <stdarg.h>
#include "config.h"
void debug_print(const char *format, ...)
{
#ifdef PRINTS_DEBUG
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}
