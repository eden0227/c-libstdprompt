#ifndef STDPROMPT_H
#define STDPROMPT_H

#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include <float.h>

char *get_string(va_list *args, const char *format, ...) __attribute__((format(printf, 2, 3)));
#define get_string(...) get_string(NULL, __VA_ARGS__)

char get_char(const char *format, ...) __attribute__((format(printf, 1, 2)));
int get_int(const char *format, ...) __attribute__((format(printf, 1, 2)));
float get_float(const char *format, ...) __attribute__((format(printf, 1, 2)));
double get_double(const char *format, ...) __attribute__((format(printf, 1, 2)));
long get_long(const char *format, ...) __attribute__((format(printf, 1, 2)));
long long get_long_long(const char *format, ...) __attribute__((format(printf, 1, 2)));

#endif
