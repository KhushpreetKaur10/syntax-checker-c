#include <stdio.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/validator.h"

int main() {
    char line1[] = "printf(\"%d\", a);";
    char line2[] = "printf(\"%d %d\", a);";

    printf("Test 1 (Valid printf): ");
    printf(printcheck(line1, strlen(line1)) == 0 ? "PASS\n" : "FAIL\n");

    printf("Test 2 (Invalid printf): ");
    printf(printcheck(line2, strlen(line2)) == 1 ? "PASS\n" : "FAIL\n");

    return 0;
}
