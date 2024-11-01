#pragma once
#include <iostream>

extern int global_verbose;

#define VERBOSE_SILENT 0
#define VERBOSE_ERROR 1
#define VERBOSE_DEBUG 100

#define LOG_ERROR (global_verbose >= VERBOSE_ERROR)
#define LOG_DBG (global_verbose >= VERBOSE_DEBUG)

#define ERR(x) if(LOG_ERROR) std::cerr <<  "c [TinyCheck] [ERROR] " << x << std::endl
// #ifdef NDEBUG
//     #define DBG(x)
// #else
    #define DBG(x) if(LOG_DBG) std::cerr <<  "c [TinyCheck] [DEBUG] " << x << std::endl 
// #endif

#define ALERT(x) std::cout << "c [TinyCheck] " << x << std::endl;