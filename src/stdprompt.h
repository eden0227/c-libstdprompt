#ifndef STDPROMPT_H
#define STDPROMPT_H

#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include <float.h>

// Prompt user for line of characters from standard input
// Return string (char *) value. If user inputs only line ending, returns "" not NULL
// Support CR (Mac OS), LF (Linux), and CRLF (Windows) as line endings
// Return NULL on errors or no input (EOF)
// Store string on heap, library destructor frees memory on program exit
// Format prompt like printf(3) function for user
char *get_string(va_list *args, const char *format, ...) __attribute__((format(printf, 2, 3)));
#define get_string(...) get_string(NULL, __VA_ARGS__)

// Prompt user for line of characters from standard input using get_string function
// Return char value. If string does not represent single char, prompt user to retry
// Return CHAR_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
char get_char(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return unsigned char value. If string does not represent single char, prompt user to retry
// Return UCHAR_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
unsigned char get_unsigned_char(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return int value. If string does not represent int in [INT_MIN, INT_MAX], prompt user to retry
// Return INT_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
int get_int(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return unsigned int value. If string does not represent unsigned int in [0, UINT_MAX], prompt user to retry
// Return UINT_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
unsigned int get_unsigned_int(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return long value. If string does not represent long in [LONG_MIN, LONG_MAX], prompt user to retry
// Return LONG_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
long get_long(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return unsigned long value. If string does not represent unsigned long in [0, ULONG_MAX], prompt user to retry
// Return ULONG_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
unsigned long get_unsigned_long(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return long long value. If string does not represent long long in [LLONG_MIN, LLONG_MAX], prompt user to retry
// Return LLONG_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
long long get_long_long(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return unsigned long long value. If string does not represent unsigned long long in [0, ULLONG_MAX], prompt user to retry
// Return ULLONG_MAX as sentinel value if string cannot be read
// Format prompt like printf(3) function for user
unsigned long long get_unsigned_long_long(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return float value. If string does not represent float in [-FLT_MAX, FLT_MAX], prompt user to retry
// Return FLT_MAX as sentinel value if string cannot be read
// Ignore finite subnormal numbers
// Format prompt like printf(3) function for user
float get_float(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return double value. If string does not represent double in [-DBL_MAX, DBL_MAX], prompt user to retry
// Return DBL_MAX as sentinel value if string cannot be read
// Ignore finite subnormal numbers
// Format prompt like printf(3) function for user
double get_double(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Prompt user for line of characters from standard input using get_string function
// Return long double value. If string does not represent long double in [-LDBL_MAX, LDBL_MAX], prompt user to retry
// Return LDBL_MAX as sentinel value if string cannot be read
// Ignore finite subnormal numbers
// Format prompt like printf(3) function for user
long double get_long_double(const char *format, ...) __attribute__((format(printf, 1, 2)));

#endif
