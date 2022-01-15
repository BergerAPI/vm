#pragma once

/**
 * Throwing an error and stopping the program.
 * @param msg
 * @param ...
 */
void log_error(char *msg, ...);

/**
 * Debugging message which will be printed only if the DEBUG flag is set.
 * @param msg
 * @param ...
 */
void log_debug(char *msg, ...);

/**
 * Logging some informations.
 * @param msg
 * @param ...
 */
void log_info(char *msg, ...);