# Custom C Library for Standard Input (`stdprompt.h`)

> Safe and efficient API for raw C input

---

## Table of Contents

-   [About](#about)
-   [Documentation](#documentation)
-   [Usage](#usage)
-   [GCC CLI](#gcc-cli)
-   [Changelog](#changelog)
-   [Contributing](#contributing)
-   [Acknowledgements](#acknowledgements)
-   [Licence](#licence)

---

## About

This is a modified, extended version of `cs50.h` C library, built for more flexibility without losing the simplicity of the original. It includes:

-   Input functions for standard types (`char *`, `char`, `int`, `long`, `long long`, `float`, `double`, `long double`) including `unsigned` variants
-   Refactored code for cleaner, more predictable behaviour
-   Efficient string allocation using exponential growth on buffer capacity
-   Support for scientific notation and exponents in floating-point values
-   Sentinel values for all data types for consistent error handling
-   Portable across commonly used compilers (**MSVC**, **GCC**, **Clang**, **MinGW**)
-   Automatic memory cleanup for dynamic array of allocated strings at program termination

Perfect for learners, hobbyists, or anyone looking to go beyond the standard CS50 C library.

---

## Documentation

### get_string

-   Prompt user for line of characters from standard input
-   Return string (**char \***) value. If user inputs only line ending, returns "" not NULL
-   Support CR (Mac OS), LF (Linux), and CRLF (Windows) as line endings
-   Return **NULL** on errors or no input (EOF)
-   Store string on heap, library destructor frees memory on program exit
-   Format prompt like printf(3) function for user
-   `char *get_string(const char *format, ...)`
-   Example:
    ```
    char *str = get_string("Input: ");
    if (str == NULL) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %s\n", str);
    ```

### get_char

-   Prompt user for line of characters from standard input using get_string function
-   Return **char** value. If string does not represent single char, prompt user to retry
-   Return **CHAR_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `char get_char(const char *format, ...)`
-   Example:
    ```
    char c = get_char("Input: ");
    if (c == CHAR_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %c\n", c);
    ```

### get_unsigned_char

-   Prompt user for line of characters from standard input using get_string function
-   Return **unsigned char** value. If string does not represent single char, prompt user to retry
-   Return **UCHAR_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `unsigned char get_unsigned_char(const char *format, ...)`
-   Example:
    ```
    unsigned char c = get_unsigned_char("Input: ");
    if (c == UCHAR_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %u\n", c);
    ```

### get_int

-   Prompt user for line of characters from standard input using get_string function
-   Return **int** value. If string does not represent int in [INT_MIN, INT_MAX], prompt user to retry
-   Return **INT_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `int get_int(const char *format, ...)`
-   Example:
    ```
    int val = get_int("Input: ");
    if (val == INT_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %i\n", val);
    ```

### get_unsigned_int

-   Prompt user for line of characters from standard input using get_string function
-   Return **unsigned int** value. If string does not represent unsigned int in [0, UINT_MAX], prompt user to retry
-   Return **UINT_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `unsigned int get_unsigned_int(const char *format, ...)`
-   Example:
    ```
    unsigned int val = get_unsigned_int("Input: ");
    if (val == UINT_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %u\n", val);
    ```

### get_long

-   Prompt user for line of characters from standard input using get_string function
-   Return **long** value. If string does not represent long in [LONG_MIN, LONG_MAX], prompt user to retry
-   Return **LONG_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `long get_long(const char *format, ...)`
-   Example:
    ```
    long val = get_long("Input: ");
    if (val == LONG_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %ld\n", val);
    ```

### get_unsigned_long

-   Prompt user for line of characters from standard input using get_string function
-   Return **unsigned long** value. If string does not represent unsigned long in [0, ULONG_MAX], prompt user to retry
-   Return **ULONG_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `unsigned long get_unsigned_long(const char *format, ...)`
-   Example:
    ```
    unsigned long val = get_unsigned_long("Input: ");
    if (val == ULONG_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %lu\n", val);
    ```

### get_long_long

-   Prompt user for line of characters from standard input using get_string function
-   Return **long long** value. If string does not represent long long in [LLONG_MIN, LLONG_MAX], prompt user to retry
-   Return **LLONG_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `long long get_long_long(const char *format, ...)`
-   Example:
    ```
    long long val = get_long_long("Input: ");
    if (val == LLONG_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %lld\n", val);
    ```

### get_unsigned_long_long

-   Prompt user for line of characters from standard input using get_string function
-   Return **unsigned long long** value. If string does not represent unsigned long long in [0, ULLONG_MAX], prompt user to retry
-   Return **ULLONG_MAX** as sentinel value if string cannot be read
-   Format prompt like printf(3) function for user
-   `unsigned long long get_unsigned_long_long(const char *format, ...)`
-   Example:
    ```
    unsigned long long val = get_unsigned_long_long("Input: ");
    if (val == ULLONG_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %llu\n", val);
    ```

### get_float

-   Prompt user for line of characters from standard input using get_string function
-   Return **float** value. If string does not represent float in [-FLT_MAX, FLT_MAX], prompt user to retry
-   Return **FLT_MAX** as sentinel value if string cannot be read
-   Ignore finite subnormal numbers
-   Format prompt like printf(3) function for user
-   `float get_float(const char *format, ...)`
-   Example:
    ```
    float val = get_float("Input: ");
    if (val == FLT_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %.*f\n", FLT_DIG, val);
    ```

### get_double

-   Prompt user for line of characters from standard input using get_string function
-   Return **double** value. If string does not represent double in [-DBL_MAX, DBL_MAX], prompt user to retry
-   Return **DBL_MAX** as sentinel value if string cannot be read
-   Ignore finite subnormal numbers
-   Format prompt like printf(3) function for user
-   `double get_double(const char *format, ...)`
-   Example:
    ```
    double val = get_double("Input: ");
    if (val == DBL_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %.*lf\n", DBL_DIG, val);
    ```

### get_long_double

-   Prompt user for line of characters from standard input using get_string function
-   Return **long double** value. If string does not represent long double in [-LDBL_MAX, LDBL_MAX], prompt user to retry
-   Return **LDBL_MAX** as sentinel value if string cannot be read
-   Ignore finite subnormal numbers
-   Format prompt like printf(3) function for user
-   `long double get_long_double(const char *format, ...)`
-   Example:
    ```
    long double val = get_long_double("Input: ");
    if (val == LDBL_MAX) // Sentinel value
    {
        // Error handling
    }
    printf("Output: %.*Lf\n", LDBL_DIG, val);
    ```

> [!IMPORTANT]
> Sentinel values are used as indicators, but the value itself can be returned and used normally.

---

## Usage

> [!NOTE]
> This is a simple, manual way to use the `stdprompt.h` C library.

-   Include the header in the source file:

    ```
    #include "<src>/stdprompt.h"
    ```

-   Compile the main program together with `stdprompt.c` and link with the math library:
    ```
    gcc <program>.c stdprompt.c -o <output> -lm
    ```
    or
    ```
    clang <program>.c stdprompt.c -o <output> -lm
    ```
    or
    ```
    cl <program>.c stdprompt.c /Fe:<output>.exe
    ```

> [!NOTE]
> Functionality in `stdprompt.c` depends on functions from `<math.h>`. For GCC/Clang/MinGW, the math library (`-lm`) must be linked. MSVC includes the math library by default.

---

## GCC CLI

A simple GCC CLI program can be used to test the output of selected data type from `stdprompt.h` functions.

> [!TIP]
> Use the provided Makefile to compile the program with `stdprompt.h`.

-   Run without arguments to display usage:

    ```
    ./gcc-test
    ```

    ```

    Usage: ./gcc-test <type>
    Run './gcc-test --help' for list of types.

    ```

-   Run with `--help` to list all supported data types:

    ```
    ./gcc-test --help
    ```

    ```

    Usage: ./gcc-test <type>
    +-----------+
    | Type      |
    +-----------+
    | str       |
    | char      |
    | uchar     |
    | int       |
    | uint      |
    | long      |
    | ulong     |
    | llong     |
    | ullong    |
    | float     |
    | double    |
    | ldouble   |
    +-----------+

    ```

-   Run with an invalid type to see the error messages:

    ```
    ./gcc-test string
    ```

    ```

    Error: Unknown type 'string'
    Run './gcc-test --help' for list of types.

    ```

-   Run with a valid type to enter input and view output:

    ```
    ./gcc-test str
    ```

    ```

    Type  : str
    Input :

    ```

    ```

    Type  : str
    Input : hello, world
    Output: hello, world

    ```

---

## Changelog

### [v3.0]

-   Add test program and source file ([tests](tests))
-   Add code comments

### [v2.0]

-   Add unsigned functions
-   Add long double function
-   Add code comments

### [v1.1]

-   Refactor get_string function
-   Refactor wrapper functions
-   Add code comments

### [v1.0]

-   Add source files ([src](src))
-   Add Makefile ([Makefile](Makefile))
-   Add documentation and guide ([README.md](README.md))

### [v0.1]

-   Initialise Git repository
-   Add GPL-3.0 licence ([LICENSE](LICENSE))

---

## Contributing

_Contribution and guidelines are not yet available (to be implemented in the future)_

---

## Acknowledgements

### Credits

-   Eternal gratitude to God, the Most Gracious, the Most Merciful.
-   Thanks to CS50 staff for making their C library ([libcs50](https://github.com/cs50/libcs50)) available for everyone.

### References

-   https://github.com/cs50/libcs50
-   https://manual.cs50.io/

---

## Licence

This project is licensed under the [GPL-3.0 Licence](LICENSE).
