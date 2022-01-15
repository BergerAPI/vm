#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define DEBUG 1

void log_error(char *msg, ...)
{
    // Printing in red
    printf("\033[0;31m [ERROR] ");

    // Printing the error message
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    printf("\033[0m\n");

    exit(1);
}

void log_debug(char *msg, ...)
{
#ifdef DEBUG
    // Printing in blue
    printf("\033[0;34m [DEBUG] ");

    // Printing the error message
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    // new line
    printf("\033[0m\n");
#endif
}

void log_info(char *msg, ...)
{
    // Printing in green
    printf("\033[0;32m [INFO] ");

    // Printing the error message
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    printf("\033[0m\n");
}