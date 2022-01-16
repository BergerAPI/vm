#include "logger.h"
#include "stdarg.h"
#include <iostream>

void log_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Printing in red: [ERROR] <message>
    std::cout << "\033[1;31m[ERROR]\033[0m ";
    vprintf(format, args);
    std::cout << std::endl;

    va_end(args);
}

void log_debug(const char *format, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, format);

    // Printing in blue: [DEBUG] <message>
    std::cout << "\033[1;34m[DEBUG]\033[0m ";
    vprintf(format, args);
    std::cout << std::endl;

    va_end(args);
#endif
}

void log_info(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Printing in green: [INFO] <message>
    std::cout << "\033[1;32m[INFO]\033[0m ";
    vprintf(format, args);
    std::cout << std::endl;

    va_end(args);
}