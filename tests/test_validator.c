#include <stdio.h>
#include "../include/validator.h"

void test_printf_valid() {
    char line[] = "printf(\"%d\", a);";

    if (!printcheck(line, strlen(line)))
        printf("PASS: printf valid\n");
    else
        printf("FAIL: printf valid\n");
}

void test_printf_invalid() {
    char line[] = "printf(\"%d %d\", a);";

    if (printcheck(line, strlen(line)))
        printf("PASS: printf invalid\n");
    else
        printf("FAIL: printf invalid\n");
}