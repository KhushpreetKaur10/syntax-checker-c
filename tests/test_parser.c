#include <stdio.h>
#include <string.h>
#include "../include/parser.h"

void test_extractFormat() {
    char line[] = "printf(\"Hello %d\", a);";
    char format[100];

    int result = extractFormat(line, format);

    if (result && strcmp(format, "Hello %d") == 0)
        printf("PASS: extractFormat\n");
    else
        printf("FAIL: extractFormat\n");
}