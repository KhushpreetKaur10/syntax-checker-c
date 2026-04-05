#include <stdio.h>
#include "models/fileline.h"

#include "include/cleaner.h"
#include "include/file_handler.h"
#include "include/keyword.h"
#include "include/bracket.h"
#include "include/builtin.h"
#include "include/function.h"
#include "include/variables.h"
#include "include/parser.h"
#include "include/validator.h"
#include "include/syntax.h"
#include "include/undeclared.h"
#include "include/duplicate.h"
#define INPUT_FILE "data/input.txt"

int main() {
    FILE *input = fopen(INPUT_FILE, "r");
    if (input == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fileLine lines[300];
    int totalLen = 0;

    removeCommentsAndStore(input, lines, &totalLen);

    printf("------ CLEAN CODE ------\n");
    printToFileAndConsole(lines, totalLen); //Actually: pointer → &lines[0] ...So function directly accesses original array ✅

    printf("\n\n------ BRACKET CHECK ------\n");
    bracket(lines, totalLen);

    printf("\n------ KEYWORDS ------\n");
    keyword(lines, totalLen);

    printf("\n------ TOTAL NUMBER OF BUILTIN FUNCTIONS USED ------\n");
    builtinfunction(lines, totalLen);

    printf("\n------ TOTAL FUNCTIONS USED ------\n");
    function_and_prototype_count(lines, totalLen);

    printf("\n------ VARIABLES WITH COUNTS ------\n");
    varcount(lines, totalLen);

    printf("\n------ SYNTAX CHECK ------\n");
    fcheck(lines, totalLen);

    printf("\n------ PRINTF / SCANF CHECK ------\n");
    printscan(lines, totalLen);

    printf("\n------ UNDECLARED VARIABLE CHECK ------\n");
    undeclaredVariables(lines, totalLen);

    printf("\n------ DUPLICATE VARIABLE CHECK ------\n");
    duplicateVariables(lines, totalLen);

    printf("\n\nTotal valid lines: %d\n", totalLen);

    fclose(input);
    return 0;
}
