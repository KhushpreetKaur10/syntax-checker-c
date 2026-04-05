#include "../include/file_handler.h"
#include <stdio.h>

//PRINT
void printToFileAndConsole(fileLine lines[], int len) {
    FILE *fout = fopen("output.txt", "w");
    if (fout == NULL) {
        printf("Error opening output file\n");
        return;
    }
    for (int i = 0; i < len; i++) {
        fprintf(fout, "Line %d [%d]: %s", 
            lines[i].lineNo, 
            lines[i].lineLen, 
            lines[i].lineText);
        printf("Line %d [%d]: %s", 
            lines[i].lineNo, 
            lines[i].lineLen, 
            lines[i].lineText);
    }
    fclose(fout);
}