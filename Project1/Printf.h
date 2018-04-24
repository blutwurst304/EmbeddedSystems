#pragma once
#include <stdarg.h>
char* Printf(char* dst, const void* end, const char* fmt, ...);
char* Printf(char* dst, const void* end, const char* fmt, va_list args);
