#pragma once

// Define debug levels
#define DEBUG_LEVEL_NONE 0
#define DEBUG_LEVEL_ERROR 1
#define DEBUG_LEVEL_WARNING 2
#define DEBUG_LEVEL_INFO 3
#define DEBUG_LEVEL_VERBOSE 4

// Set current debug level (Change this as needed for your project)
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DEBUG_LEVEL_ERROR
#endif

// Debug macro with default level
#if defined(DEBUG) && (DEBUG_LEVEL > DEBUG_LEVEL_NONE)
#include <iostream>
#define DB(...) _DB_IMPL(__VA_ARGS__, DEBUG_LEVEL_VERBOSE)
#define _DB_IMPL(code, level, ...) \
    if (level <= DEBUG_LEVEL)      \
    {                              \
        code;                      \
    }
#else
#define DB(...)
#endif