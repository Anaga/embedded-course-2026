#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define MAX_HEIGHT 80

static int read_int_in_range(const char *prompt, int min, int max);
static void print_christmas_tree(int height);
static void print_n_chars(char ch, int count);

int main(void)
{
    int height = read_int_in_range("Enter tree height (1..80): ", 1, MAX_HEIGHT);
    print_christmas_tree(height);
    return 0;
}

/*
 * read_int_in_range()
 *
 * Reads an integer from stdin and validates:
 *  - numeric conversion using strtol
 *  - no trailing invalid characters
 *  - no overflow (ERANGE)
 *  - value within [min, max]
 */

static int read_int_in_range(const char *prompt, int min, int max)
{
    char buf[128];

    for (;;) {
        long val;
        char *end = NULL;

        printf("%s", prompt);

        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or input error */
            printf("\nInput error. Exiting.\n");
            exit(1);
        }

        errno = 0;
        val = strtol(buf, &end, 10);

        /* Check for conversion failure (no digits found) */
        if (end == buf) {
            printf("Please enter a number.\n");
            continue;
        }

        /* Detect overflow or underflow */
        if (errno == ERANGE || val < LONG_MIN || val > LONG_MAX) {
            printf("Number out of range.\n");
            continue;
        }

        /* Skip trailing whitespace */
        while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
            end++;
        }

        /* Reject input with extra non-whitespace characters */
        if (*end != '\0') {
            printf("Invalid characters after the number.\n");
            continue;
        }

        if (val < min || val > max) {
            printf("Please enter a value between %d and %d.\n", min, max);
            continue;
        }

        return (int)val;
    }
}

static void print_christmas_tree(int height)
{
    for (int i = 1; i <= height; i++) {
        int spaces = height - i;
        int stars  = 2 * i - 1;

        print_n_chars(' ', spaces);
        print_n_chars('*', stars);
        putchar('\n');
    }
}

static void print_n_chars(char ch, int count)
{
    for (int i = 0; i < count; i++) {
        putchar(ch);
    }
}
