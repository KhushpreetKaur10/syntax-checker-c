#include "../include/variables.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getTypeIndex(char *word);
int getArraySize(char *str);


//👉 Read line → detect type → combine lines → detect end → split variables → check array → compute memory
void varcount(fileLine arr[], int len)
{
    const char *types[] = {"int", "char", "long", "double", "float", "short"};

    int total[6] = {0};
    int memory[6] = {0};

    for (int i = 0; i < len; i++)
    {
        char line[200];
        strcpy(line, arr[i].lineText);

        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;

        if (strlen(ptr) == 0) continue;

        // ❌ skip function definitions
        if (strchr(ptr, '(') && strchr(ptr, ')'))
            continue;

        // ❌ skip struct or invalid lines
        if (strstr(ptr, "struct") || strchr(ptr, '{') || strchr(ptr, '}'))
            continue;

        // extract type
        char temp[200];
        strcpy(temp, ptr);

        char *token = strtok(temp, " \t;");
        int typeIndex = getTypeIndex(token);

        if (typeIndex == -1) continue;

        // get rest after type
        char *rest = strchr(ptr, ' ');
        if (!rest) continue;
        rest++;

        char vars[200];
        strcpy(vars, rest);

        char *var = strtok(vars, ",;");

        while (var != NULL)
        {
            while (*var == ' ' || *var == '\t') var++;

            if (strlen(var) == 0){
                var = strtok(NULL, ",;");
                continue;
            }

            // remove initialization
            char *eq = strchr(var, '=');
            if (eq) *eq = '\0';

            // remove brackets name[i]
            char name[50];
            int k = 0;
            for (int j = 0; var[j] && var[j] != '['; j++)
                name[k++] = var[j];
            name[k] = '\0';

            // skip invalid identifiers
            if (!isalpha(name[0])) {
                var = strtok(NULL, ",;");
                continue;
            }

            int size = 1;
            if (strchr(var, '['))
                size = getArraySize(var);

            total[typeIndex] += size;

            int bytes =
                (typeIndex == 0 ? sizeof(int) :
                typeIndex == 1 ? sizeof(char) :
                typeIndex == 2 ? sizeof(long) :
                typeIndex == 3 ? sizeof(double) :
                typeIndex == 4 ? sizeof(float) :
                sizeof(short));

            memory[typeIndex] += size * bytes;

            var = strtok(NULL, ",;");
        }
    }

    printf("Total int: %d\nTotal char: %d\nTotal long: %d\nTotal double: %d\nTotal float: %d\nTotal short: %d\n",
           total[0], total[1], total[2], total[3], total[4], total[5]);

    printf("\nMEMORY CONSUMED\n");
    printf("int: %d bytes\nchar: %d bytes\nlong: %d bytes\ndouble: %d bytes\nfloat: %d bytes\nshort: %d bytes\n",
           memory[0], memory[1], memory[2], memory[3], memory[4], memory[5]);
}


//DETECT VARIABLE TYPE
int getVarType(char *var){
    // remove &
    if (var[0] == '&') var++;
    // simple heuristic
    if (strstr(var, "int")) return 0;
    if (strstr(var, "float")) return 1;
    if (strstr(var, "double")) return 2;
    if (strstr(var, "char")) return 3;

    return -1;
}


int getArraySize(char *str) {
    int size = 0;
    char num[20];
    int k = 0;

    while (*str && *str != '[') str++;
    if (*str == '[') str++;

    while (*str && *str != ']') {
        if (isdigit(*str))
            num[k++] = *str;
        str++;
    }

    num[k] = '\0';
    if (k == 0) return 1; // safety
    return atoi(num);
}