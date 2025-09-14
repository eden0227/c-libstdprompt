#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#include "../src/stdprompt.h"

// Define available type code macro
#define STR 1
#define CHAR 2
#define UCHAR 3
#define INT 4
#define UINT 5
#define LONG 6
#define ULONG 7
#define LLONG 8
#define ULLONG 9
#define FLT 10
#define DBL 11
#define LDBL 12

typedef struct type_entry
{
    char *name;
    int code;
} type_entry;

// Initialise table of available type and code
static type_entry list[] = {
    {"str", STR},
    {"char", CHAR},
    {"uchar", UCHAR},
    {"int", INT},
    {"uint", UINT},
    {"long", LONG},
    {"ulong", ULONG},
    {"llong", LLONG},
    {"ullong", ULLONG},
    {"float", FLT},
    {"double", DBL},
    {"ldouble", LDBL},
};

// Initialise total number of types
static size_t len = sizeof(list) / sizeof(list[0]);

void print_usage(const char *program);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "\nUsage: %s <type>\n", argv[0]);
        fprintf(stderr, "Run '%s --help' for list of types.\n\n", argv[0]);
        return 1;
    }

    if (!strcmp(argv[1], "--help"))
    {
        print_usage(argv[0]);
        return 0;
    }

    // Initialise code for type
    int code = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (!strcmp(argv[1], list[i].name))
        {
            code = list[i].code; // Store code of valid input type
            break;
        }
    }

    if (!code)
    {
        fprintf(stderr, "\nError: Unknown type '%s'\n", argv[1]);
        fprintf(stderr, "Run '%s --help' for list of types.\n\n", argv[0]);
        return 2;
    }

    // Test input for selected type
    switch (code)
    {
    case STR:
    {
        printf("\nType  : %s\n", argv[1]);

        char *str = get_string("Input : ");
        if (str == NULL) // Sentinel value
        {
            printf("Error: Unable to allocate string\n\n");
            return 3;
        }

        printf("Output: %s\n\n", str);
        break;
    }

    case CHAR:
    {
        printf("\nType  : %s\n", argv[1]);

        char c = get_char("Input : ");
        if (c == CHAR_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate char or sentinel value\n\n");
            return 3;
        }

        printf("Output: %c\n\n", c);
        break;
    }

    case UCHAR:
    {
        printf("\nType  : %s\n", argv[1]);

        unsigned char c = get_unsigned_char("Input : ");
        if (c == UCHAR_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate unsigned char or sentinel value\n\n");
            return 3;
        }

        printf("Output: %u\n\n", c);
        break;
    }

    case INT:
    {
        printf("\nType  : %s\n", argv[1]);

        int val = get_int("Input : ");
        if (val == INT_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate int or sentinel value\n\n");
            return 3;
        }

        printf("Output: %i\n\n", val);
        break;
    }

    case UINT:
    {
        printf("\nType  : %s\n", argv[1]);

        unsigned int val = get_unsigned_int("Input : ");
        if (val == UINT_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate unsigned int or sentinel value\n\n");
            return 3;
        }

        printf("Output: %u\n\n", val);
        break;
    }

    case LONG:
    {
        printf("\nType  : %s\n", argv[1]);

        long val = get_long("Input : ");
        if (val == LONG_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate long or sentinel value\n\n");
            return 3;
        }

        printf("Output: %ld\n\n", val);
        break;
    }

    case ULONG:
    {
        printf("\nType  : %s\n", argv[1]);

        unsigned long val = get_unsigned_long("Input : ");
        if (val == ULONG_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate unsigned long or sentinel value\n\n");
            return 3;
        }

        printf("Output: %lu\n\n", val);
        break;
    }

    case LLONG:
    {
        printf("\nType  : %s\n", argv[1]);

        long long val = get_long_long("Input : ");
        if (val == LLONG_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate long long or sentinel value\n\n");
            return 3;
        }

        printf("Output: %lld\n\n", val);
        break;
    }

    case ULLONG:
    {
        printf("\nType  : %s\n", argv[1]);

        unsigned long long val = get_unsigned_long_long("Input : ");
        if (val == ULLONG_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate unsigned long long or sentinel value\n\n");
            return 3;
        }

        printf("Output: %llu\n\n", val);
        break;
    }

    case FLT:
    {
        printf("\nType  : %s\n", argv[1]);

        float val = get_float("Input : ");
        if (val == FLT_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate float or sentinel value\n\n");
            return 3;
        }

        printf("Output: %.*f\n\n", FLT_DIG, val);
        break;
    }

    case DBL:
    {
        printf("\nType  : %s\n", argv[1]);

        double val = get_double("Input : ");
        if (val == DBL_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate double or sentinel value\n\n");
            return 3;
        }

        printf("Output: %.*lf\n\n", DBL_DIG, val);
        break;
    }

    case LDBL:
    {
        printf("\nType  : %s\n", argv[1]);

        long double val = get_long_double("Input : ");
        if (val == LDBL_MAX) // Sentinel value
        {
            printf("Error: Unable to allocate long double or sentinel value\n\n");
            return 3;
        }

        printf("Output: %.*Lf\n\n", LDBL_DIG, val);
        break;
    }

    default:
        fprintf(stderr, "\nError: Bad code for type '%s'\n", argv[1]);
        fprintf(stderr, "Run '%s --help' for list of types.\n\n", argv[0]);
        return 4;
    }

    return 0;
}

// Print usage and table of types
void print_usage(const char *program)
{
    // Print usage above table
    printf("\nUsage: %s <type>\n", program);

    // Initialise max length of type
    size_t max = 0;

    for (size_t i = 0; i < len; i++)
    {
        size_t n = strlen(list[i].name);
        if (n > max)
            max = n;
    }

    // Initialise row width
    size_t width = max + 2;

    // Print top border including edges
    printf("+");
    for (size_t i = 0; i < width + 2; i++)
        printf("-");
    printf("+\n");

    // Print type row
    printf("| %-*s |\n", (int)width, "Type");

    // Print bottom border for type row
    printf("+");
    for (size_t i = 0; i < width + 2; i++)
        printf("-");
    printf("+\n");

    // Print each row
    for (size_t i = 0; i < len; i++)
        printf("| %-*s |\n", (int)width, list[i].name);

    // Print bottom border for last row
    printf("+");
    for (size_t i = 0; i < width + 2; i++)
        printf("-");
    printf("+\n\n");
}
