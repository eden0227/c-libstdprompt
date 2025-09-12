#define _GNU_SOURCE

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

#include "stdprompt.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"

#define BUFFER_CAPACITY 16

static char **strings = NULL;
static size_t allocations = 0;

#undef get_string
char *get_string(va_list *args, const char *format, ...)
{
    if (allocations >= SIZE_MAX / sizeof(char *))
        return NULL;

    if (format != NULL)
    {
        va_list ap;

        if (args == NULL)
            va_start(ap, format);
        else
            va_copy(ap, *args);

        vprintf(format, ap);
        va_end(ap);
    }

    size_t capacity = BUFFER_CAPACITY;
    unsigned char *buffer = malloc(capacity);
    if (buffer == NULL)
        return NULL;

    int c;
    size_t size = 0;

    while ((c = fgetc(stdin)) != '\r' && c != '\n' && c != EOF)
    {
        if (size + 1 > capacity)
        {
            if (capacity >= SIZE_MAX / 2)
            {
                free(buffer);
                return NULL;
            }

            capacity *= 2;

            unsigned char *temp = realloc(buffer, capacity);
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        buffer[size++] = c;
    }

    if (size == 0 && c == EOF)
    {
        free(buffer);
        return NULL;
    }

    if (size == SIZE_MAX)
    {
        free(buffer);
        return NULL;
    }

    if (c == '\r')
    {
        int next = fgetc(stdin);
        if (next != '\n' && next != EOF)
            if (ungetc(next, stdin) == EOF)
            {
                free(buffer);
                return NULL;
            }
    }

    unsigned char *str = realloc(buffer, size + 1);
    if (str == NULL)
    {
        free(buffer);
        return NULL;
    }
    str[size] = '\0';

    char **temp = realloc(strings, sizeof(char *) * (allocations + 1));
    if (temp == NULL)
    {
        free(str);
        return NULL;
    }
    strings = temp;

    strings[allocations++] = (char *)str;
    return (char *)str;
}

char get_char(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    while (true)
    {
        char *str = get_string(&ap, format);
        if (str == NULL)
        {
            va_end(ap);
            return CHAR_MAX;
        }

        while (isspace((unsigned char)*str))
            str++;

        if (*str == '\0')
            continue;

        char *end = str + strlen(str) - 1;
        while (end > str && isspace((unsigned char)*end))
            *end-- = '\0';

        if (*(str + 1) == '\0')
        {
            va_end(ap);
            return (char)*str;
        }
    }
}

int get_int(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    while (true)
    {
        char *str = get_string(&ap, format);
        if (str == NULL)
        {
            va_end(ap);
            return INT_MAX;
        }

        while (isspace((unsigned char)*str))
            str++;

        if (*str)
        {
            errno = 0;
            char *end;
            long num = strtol(str, &end, 10);

            while (isspace((unsigned char)*end))
                end++;

            if (errno == 0 && *end == '\0' && num >= INT_MIN && num <= INT_MAX)
            {
                va_end(ap);
                return (int)num;
            }
        }
    }
}

float get_float(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    while (true)
    {
        char *str = get_string(&ap, format);
        if (str == NULL)
        {
            va_end(ap);
            return FLT_MAX;
        }

        while (isspace((unsigned char)*str))
            str++;

        if (*str)
        {
            errno = 0;
            char *end;
            float flt = strtof(str, &end);

            while (isspace((unsigned char)*end))
                end++;

            if (errno == 0 && *end == '\0' && isfinite(flt) && flt >= -FLT_MAX && flt <= FLT_MAX)
            {
                va_end(ap);
                return flt;
            }
        }
    }
}

double get_double(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    while (true)
    {
        char *str = get_string(&ap, format);
        if (str == NULL)
        {
            va_end(ap);
            return DBL_MAX;
        }

        while (isspace((unsigned char)*str))
            str++;

        if (*str)
        {
            errno = 0;
            char *end;
            double dbl = strtod(str, &end);

            while (isspace((unsigned char)*end))
                end++;

            if (errno == 0 && *end == '\0' && isfinite(dbl) && dbl >= -DBL_MAX && dbl <= DBL_MAX)
            {
                va_end(ap);
                return dbl;
            }
        }
    }
}

long get_long(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    while (true)
    {
        char *str = get_string(&ap, format);
        if (str == NULL)
        {
            va_end(ap);
            return LONG_MAX;
        }

        while (isspace((unsigned char)*str))
            str++;

        if (*str)
        {
            errno = 0;
            char *end;
            long num = strtol(str, &end, 10);

            while (isspace((unsigned char)*end))
                end++;

            if (errno == 0 && *end == '\0' && num >= LONG_MIN && num <= LONG_MAX)
            {
                va_end(ap);
                return num;
            }
        }
    }
}

long long get_long_long(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    while (true)
    {
        char *str = get_string(&ap, format);
        if (str == NULL)
        {
            va_end(ap);
            return LLONG_MAX;
        }

        while (isspace((unsigned char)*str))
            str++;

        if (*str)
        {
            errno = 0;
            char *end;
            long long num = strtoll(str, &end, 10);

            while (isspace((unsigned char)*end))
                end++;

            if (errno == 0 && *end == '\0' && num >= LLONG_MIN && num <= LLONG_MAX)
            {
                va_end(ap);
                return num;
            }
        }
    }
}

static void teardown(void)
{
    if (strings != NULL)
    {
        for (size_t i = 0; i < allocations; i++)
            free(strings[i]);
        free(strings);
    }
}

#if defined(_MSC_VER)
#pragma section(".CRT$XCU", read)
#define INITIALISER_(FUNC, PREFIX)                                 \
    static void FUNC(void);                                        \
    __declspec(allocate(".CRT$XCU")) void (*FUNC##_)(void) = FUNC; \
    __pragma(comment(linker, "/include:" PREFIX #FUNC "_")) static void FUNC(void)
#ifdef _WIN64
#define INITIALISER(FUNC) INITIALISER_(FUNC, "")
#else
#define INITIALISER(FUNC) INITIALISER_(FUNC, "_")
#endif
#elif defined(__GNUC__)
#define INITIALISER(FUNC)                                \
    static void FUNC(void) __attribute__((constructor)); \
    static void FUNC(void)
#else
#error The library requires compiler-specific features. Refer to the source code and documentation.
#endif

INITIALISER(setup)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    atexit(teardown);
}

#pragma GCC diagnostic pop
