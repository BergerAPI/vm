#pragma once

#define DEBUG 1

/**
 * @brief Basically throwing an error
 * 
 * @param format 
 * @param ... 
 */
void log_error(const char *format, ...);

/**
 * @brief Debug messsages, only shown if DEBUG is defined
 * 
 * @param format 
 * @param ... 
 */
void log_debug(const char *format, ...);

/**
 * @brief Logging basic informations
 * 
 * @param format 
 * @param ... 
 */
void log_info(const char *format, ...);