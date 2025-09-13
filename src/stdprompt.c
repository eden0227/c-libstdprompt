// Enable GNU-specific attributes in standard libraries
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

// Disable warnings on variadic arguments from compilers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"

// Define initial macro for buffer capacity in get_string function
#define BUFFER_CAPACITY 16

// Initialise dynamic array of allocated strings by get_string function
static char **strings = NULL;
static size_t allocations = 0;

// Prompt user for line of characters from standard input
// Return string (char *) value. If user inputs only line ending, returns "" not NULL
// Support CR (\r), LF (\n), and CRLF (\r\n) as line endings
// Return NULL on errors or no input (EOF)
// Store string on heap, library destructor frees memory on program exit
#undef get_string
char *get_string(va_list *args, const char *format, ...)
{
    // Check for space in dynamic array
    if (allocations >= SIZE_MAX / sizeof(char *))
        return NULL;

    // Prompt user using formatted string with variadic arguments
    if (format != NULL)
    {
        va_list ap;

        if (args == NULL)
            va_start(ap, format);
        else
            va_copy(ap, *args); // Copy wrapper function arguments into variadic list

        vprintf(format, ap);
        va_end(ap);
    }

    // Initialise dynamic buffer for characters
    size_t capacity = BUFFER_CAPACITY;
    unsigned char *buffer = malloc(capacity);
    if (buffer == NULL)
        return NULL;

    size_t size = 0; // Indicate number of characters in buffer
    int c;           // Read character or EOF

    // Get characters iteratively from standard input
    // Check CR (\r), LF (\n), and CRLF (\r\n)
    while ((c = fgetc(stdin)) != '\r' && c != '\n' && c != EOF)
    {
        if (size + 1 > capacity) // Grow buffer if necessary
        {
            if (capacity >= SIZE_MAX / 2) // Consider terminating zero
            {
                free(buffer);
                return NULL;
            }

            capacity *= 2; // Increment buffer capacity exponentially

            unsigned char *temp = realloc(buffer, capacity);
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        buffer[size++] = c; // Append current character to buffer
    }

    // Check for no input from user
    if (size == 0 && c == EOF)
    {
        free(buffer);
        return NULL;
    }

    // Check space for terminating zero
    if (size == SIZE_MAX)
    {
        free(buffer);
        return NULL;
    }

    // Check for CRLF (\r\n)
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

    // Minimise buffer
    unsigned char *str = realloc(buffer, size + 1);
    if (str == NULL)
    {
        free(buffer);
        return NULL;
    }
    str[size] = '\0'; // Terminate string

    // Resize dynamic array to append string
    char **temp = realloc(strings, sizeof(char *) * (allocations + 1));
    if (temp == NULL)
    {
        free(str);
        return NULL;
    }
    strings = temp;

    strings[allocations++] = (char *)str; // Append string to global array
    return (char *)str;                   // Return string
}

// Prompt user for line of characters from standard input using get_string function
// Return char value. If string does not represent single char, prompt user to retry
// Return CHAR_MAX as sentinel value if string cannot be read
char get_char(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get char from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return CHAR_MAX; // Return sentinel value on error
        }

        if (*str && *(str + 1) == '\0') // Accept single char
        {
            va_end(ap);
            return *str;
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        char *end = str + strlen(str) - 1;
        while (end > str && isspace((unsigned char)*end)) // Trim trailing whitespace
            *end-- = '\0';

        if (*str && *(str + 1) == '\0') // Return char if single char is provided
        {
            va_end(ap);
            return *str;
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return unsigned char value. If string does not represent single char, prompt user to retry
// Return UCHAR_MAX as sentinel value if string cannot be read
unsigned char get_unsigned_char(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get char from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return UCHAR_MAX; // Return sentinel value on error
        }

        if (*str && *(str + 1) == '\0') // Accept single char
        {
            va_end(ap);
            return (unsigned char)*str;
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        char *end = str + strlen(str) - 1;
        while (end > str && isspace((unsigned char)*end)) // Trim trailing whitespace
            *end-- = '\0';

        if (*str && *(str + 1) == '\0') // Return char if single char is provided
        {
            va_end(ap);
            return (unsigned char)*str; // Cast char to unsigned char
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return int value. If string does not represent int in [INT_MIN, INT_MAX], prompt user to retry
// Return INT_MAX as sentinel value if string cannot be read
int get_int(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get int from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return INT_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        errno = 0;
        char *end;
        long num = strtol(str, &end, 10); // Convert string to long

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && num >= INT_MIN && num <= INT_MAX)
        {
            va_end(ap);
            return (int)num; // Cast long to int
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return unsigned int value. If string does not represent unsigned int in [0, UINT_MAX], prompt user to retry
// Return UINT_MAX as sentinel value if string cannot be read
unsigned int get_unsigned_int(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get unsigned int from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return UINT_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        if (*str == '-') // Reject negative value
            continue;

        errno = 0;
        char *end;
        unsigned long num = strtoul(str, &end, 10); // Convert string to unsigned long

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && num <= UINT_MAX)
        {
            va_end(ap);
            return (unsigned int)num; // Cast unsigned long to unsigned int
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return long value. If string does not represent long in [LONG_MIN, LONG_MAX], prompt user to retry
// Return LONG_MAX as sentinel value if string cannot be read
long get_long(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get long from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return LONG_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        errno = 0;
        char *end;
        long num = strtol(str, &end, 10); // Convert string to long

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && num >= LONG_MIN && num <= LONG_MAX)
        {
            va_end(ap);
            return num; // Return long
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return unsigned long value. If string does not represent unsigned long in [0, ULONG_MAX], prompt user to retry
// Return ULONG_MAX as sentinel value if string cannot be read
unsigned long get_unsigned_long(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get unsigned long from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return ULONG_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        if (*str == '-') // Reject negative value
            continue;

        errno = 0;
        char *end;
        unsigned long num = strtoul(str, &end, 10); // Convert string to unsigned long

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && num <= ULONG_MAX)
        {
            va_end(ap);
            return num; // Return unsigned long
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return long long value. If string does not represent long long in [LLONG_MIN, LLONG_MAX], prompt user to retry
// Return LLONG_MAX as sentinel value if string cannot be read
long long get_long_long(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get long long from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return LLONG_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        errno = 0;
        char *end;
        long long num = strtoll(str, &end, 10); // Convert string to long long

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && num >= LLONG_MIN && num <= LLONG_MAX)
        {
            va_end(ap);
            return num; // Return long long
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return unsigned long long value. If string does not represent unsigned long long in [0, ULLONG_MAX], prompt user to retry
// Return ULLONG_MAX as sentinel value if string cannot be read
unsigned long long get_unsigned_long_long(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get unsigned long long from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return ULLONG_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        if (*str == '-') // Reject negative value
            continue;

        errno = 0;
        char *end;
        unsigned long long num = strtoull(str, &end, 10); // Convert string to unsigned long long

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && num <= ULLONG_MAX)
        {
            va_end(ap);
            return num; // Return unsigned long long
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return float value. If string does not represent float in [-FLT_MAX, FLT_MAX], prompt user to retry
// Return FLT_MAX as sentinel value if string cannot be read
float get_float(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get float from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return FLT_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        errno = 0;
        char *end;
        float flt = strtof(str, &end); // Convert string to float

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && isfinite(flt) && flt >= -FLT_MAX && flt <= FLT_MAX)
        {
            va_end(ap);
            return flt; // Return float
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return double value. If string does not represent double in [-DBL_MAX, DBL_MAX], prompt user to retry
// Return DBL_MAX as sentinel value if string cannot be read
double get_double(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get float from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return DBL_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        errno = 0;
        char *end;
        double dbl = strtod(str, &end); // Convert string to double

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && isfinite(dbl) && dbl >= -DBL_MAX && dbl <= DBL_MAX)
        {
            va_end(ap);
            return dbl; // Return double
        }
    }
}

// Prompt user for line of characters from standard input using get_string function
// Return long double value. If string does not represent long double in [-LDBL_MAX, LDBL_MAX], prompt user to retry
// Return LDBL_MAX as sentinel value if string cannot be read
long double get_long_double(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    // Try to get float from user
    while (true)
    {
        char *str = get_string(&ap, format); // Get line of characters
        if (str == NULL)
        {
            va_end(ap);
            return LDBL_MAX; // Return sentinel value on error
        }

        while (isspace((unsigned char)*str)) // Trim leading whitespace
            str++;

        if (*str == '\0') // Check for empty string
            continue;

        errno = 0;
        char *end;
        long double ldbl = strtold(str, &end); // Convert string to long double

        while (isspace((unsigned char)*end)) // Trim trailing whitespace
            end++;

        // Check remaining string and range
        if (errno == 0 && *end == '\0' && isfinite(ldbl) && ldbl >= -LDBL_MAX && ldbl <= LDBL_MAX)
        {
            va_end(ap);
            return ldbl; // Return long double
        }
    }
}

// Call automatically after execution exit main program
static void teardown(void)
{
    if (strings != NULL)
    {
        for (size_t i = 0; i < allocations; i++)
            free(strings[i]); // Free allocated strings
        free(strings);        // Free dynamic array
    }
}

// Define portable INITIALISER(FUNC) macro to run FUNC before main program
#if defined(_MSC_VER) // MSVC
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
#elif defined(__GNUC__) // GCC, Clang, MinGW
// Use constructor attribute to run function before main program
#define INITIALISER(FUNC)                                \
    static void FUNC(void) __attribute__((constructor)); \
    static void FUNC(void)
#else
#error The library requires compiler-specific features. Refer to the source code and documentation.
#endif

// Call automatically before execution enters main program
INITIALISER(setup)
{
    // Disable buffering for standard output
    setvbuf(stdout, NULL, _IONBF, 0);

    // Free memory for dynamic array of allocated strings
    atexit(teardown);
}

// Re-enable warnings
#pragma GCC diagnostic pop
