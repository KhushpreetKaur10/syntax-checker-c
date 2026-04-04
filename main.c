#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int lineNo;
    int lineLen;
    char lineText[300];
} fileLine;



// function declarations

//lines[] is actually treated as: fileLine *lines
//👉 So you are passing a pointer to the array (efficient, no copying)

void printToFileAndConsole(fileLine lines[], int len);
void removeCommentsAndStore(FILE *input, fileLine lines[], int *totalLen);
void keyword(fileLine arr[], int len);
void bracket(fileLine arr[], int len);
void function_and_prototype_count(fileLine arr[], int len);
void builtinfunction(fileLine arr[], int len);
void printscan(fileLine arr[], int size);
int printcheck(char arr[], int size);
int scancheck(char arr[], int size);
void varcount(fileLine arr[], int len);
int getscheck(char arr[], int size);
int putscheck(char arr[], int size);
int fprintfcheck(char arr[], int size);
int fscanfcheck(char arr[], int size);
void fcheck(fileLine arr[], int len);
int forcheck(char arr[], int size);
int whilecheck(char arr[], int size);
void undeclaredVariables(fileLine arr[], int len);
void duplicateVariables(fileLine *arr, int len);


//MAIN
int main() {
    FILE *input = fopen("input.txt", "r");
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



//---------FUNCTION DEFINITIONS--------------


//FIND COMMENTS AND REMOVE THEM
/*      Start
          │
          ▼
        Open file for reading
          │
          ▼
        Initialize:
        - inComment = 0
        - realLine = 0
        - i = 0 (index for lines[])
          │
          ▼
        Read line from file (fgets)
          │
          ▼
        Increment realLine
          │
          ▼
        Initialize:
        - result[] = ""
        - k = 0
          │
          ▼
        For each character in line:
         ├─ If not inComment and '//' → break (ignore rest of line)
         ├─ Else if not inComment and '/*' → inComment = 1, skip next char
         ├─ Else if inComment and '* /' → inComment = 0, skip next char
         └─ Else if not inComment → result[k++] = current char
          │
          ▼
        Add null terminator to result[k]
          │
          ▼
        Check if result[] is blank (only spaces/tabs/newline)
          ├─ If yes → skip storing, read next line
          └─ If no → store in lines[i]:
               - lineNo = realLine
               - lineText = result[]
               - lineLen = strlen(result)
               - i++
          │
          ▼
        Loop until EOF
          │
          ▼
        Set *totalLen = i
          │
          ▼
        End
*/
void removeCommentsAndStore(FILE *input, fileLine lines[], int *totalLen) {
    char str[300];
    int inComment = 0;
    int realLine = 0;
    int i = 0;

    while (fgets(str, 300, input) != NULL) {
        realLine++;
        char result[300] = "";
        int k = 0;
        for (int j = 0; str[j] != '\0'; j++) {
            // // comment
            if (!inComment && str[j] == '/' && str[j+1] && str[j+1] == '/') {
                break;
            }
            // /* start
            else if (!inComment && str[j] == '/' && str[j+1] && str[j+1] == '*') {
                inComment = 1;
                j++;
            }
            // */ end
            else if (inComment && str[j] == '*' && str[j+1] && str[j+1] == '/') {
                inComment = 0;
                j++;
            }
            // normal char
            else if (!inComment) {
                result[k++] = str[j];
            }
        }
        result[k] = '\0';

        // skip blank lines
        char *check = result;
        while (*check == ' ' || *check == '\t' || *check == '\n') check++;
        if (*check == '\0') continue;

        lines[i].lineNo = realLine;
        strcpy(lines[i].lineText, result);
        lines[i].lineLen = strlen(result);
        i++;
    }
    *totalLen = i;
}



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


//FIND KEYWORDS
void keyword(fileLine arr[], int len) {
    //const → ensures keywords cannot be modified
    //👉 Why pointer (char *)? Because strings are stored as addresses, not full arrays.
    const char *keywords[] = {
        "auto","double","int","struct","break","else","long","switch","case","enum","register","typedef","char","extern","return","union","const","float","short","unsigned","continue","for","signed","void","default","goto","sizeof","volatile","do","if","static","while"
    };
    // int totalKeywords = 32;
    int totalKeywords = sizeof(keywords) / sizeof(keywords[0]); //This works only when array is NOT passed as pointer as an argument to function

    for (int i = 0; i < len; i++) {
        char temp[300];
        strcpy(temp, arr[i].lineText);

        //remove strings
        int inString = 0;
        char cleaned[300];
        int k = 0;

        for (int j = 0; temp[j] != '\0'; j++) {
            if (temp[j] == '\"') {
                inString = !inString; // toggle
                continue;             // skip quotes
            }
            if (!inString) {
                cleaned[k++] = temp[j];
            }
        }
        cleaned[k] = '\0';

        char *token = strtok(cleaned, " \t\n(){}[];,+-*/=<>!&|");

        while (token != NULL) {
            for (int j = 0; j < totalKeywords; j++) {
                if (strcmp(token, keywords[j]) == 0) {
                    printf("Line %d: %s\n", arr[i].lineNo, token);
                }
            }
            token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|");
        }
    }
}


//BRACKET CHECK (STACK)
void bracket(fileLine arr[], int len) {
    char stack[1000];
    int lineStack[1000];
    int top = -1;
    int errorFound = 0;
    
    for (int i = 0; i < len; i++) {
        int inString = 0;
        for (int j = 0; j < arr[i].lineLen; j++) {
            char ch = arr[i].lineText[j];

            // ignore bracket inside strings
            if (ch == '\"') {
                inString = !inString;
                continue;
            }
            if (inString) continue;

            if (ch == '{' || ch == '(' || ch == '[') {
                stack[++top] = ch;
                lineStack[top] = arr[i].lineNo;
            }
            else if (ch == '}' || ch == ')' || ch == ']') {
                if (top == -1) {
                    printf("Line %d: Extra '%c'\n", arr[i].lineNo, ch);
                    errorFound=1;
                } else {
                    char open = stack[top--];
                    if ((open == '{' && ch != '}') ||
                    (open == '(' && ch != ')') ||
                    (open == '[' && ch != ']')) {
                        printf("Line %d: Mismatch '%c' with '%c'\n",
                            arr[i].lineNo, open, ch);
                        errorFound=1;
                    }
                }
            }
        }
    }
    while (top != -1) {
        printf("Line %d: Unmatched '%c'\n",
            lineStack[top], stack[top]);
        top--;
        errorFound=1;
    }
    if (!errorFound) {
        printf("All brackets are balanced correctly ✅\n");
    }
}


//DETECT BUILTIN FNS
void builtinfunction(fileLine arr[], int len) {
    char sync[30][20] = {
        "printf", "scanf", "gets", "puts", "fscanf", "fprintf", "fgets", "fputs", "fputc", "fgetc", "fopen", "fclose", "feof", "fflush", "malloc", "calloc", "rand", "strcmp", "strlen", "strcpy", "strncpy", "strncmp", "tolower", "toupper", "strrev", "getch", "strcat", "strncat", "sqrt","pow"
    };

    int count[30] = {0}; // store count for each function
    int total = 0;

    for (int i = 0; i < len; i++) {
        char lineCopy[200];
        strcpy(lineCopy, arr[i].lineText);

        //remove detection inside strings
        int inString = 0;
        char cleaned[200];
        int k = 0;
        for (int j = 0; lineCopy[j] != '\0'; j++) {
            if (lineCopy[j] == '\"') {
                inString = !inString; // toggle
                continue;             // skip quotes
            }
            if (!inString) {
                cleaned[k++] = lineCopy[j];
            }
        }
        cleaned[k] = '\0';

        const char *delim = " \t();,\n"; // delimiters
        char *token = strtok(cleaned, delim);

        while (token != NULL) {
            for (int j = 0; j < 30; j++) {
                if (strcmp(token, sync[j]) == 0) {
                    count[j]++;
                    total++;
                    break; // stop checking once matched
                }
            }
            token = strtok(NULL, delim);
        }
    }

    // Print individual counts
    printf("Built-in Function Counts:\n");
    for (int j = 0; j < 30; j++) {
        if (count[j] > 0) {
            printf("%s: %d\n", sync[j], count[j]);
        }
    }

    printf("Total Builtin Functions: %d\n", total);
}



//DETECT SPECIFIERS
void extractSpecifiers(char format[], char specs[][5], int *count){
    *count = 0;
    for (int i = 0; format[i]; i++){ //Equivalent to: while(format[i] != '\0')
        if (format[i] == '%' && format[i+1]){
            int k = 0;
            specs[*count][k++] = '%';
            i++;
            // handle %lf
            if (format[i] == 'l' && format[i+1] == 'f'){
                specs[*count][k++] = 'l';
                specs[*count][k++] = 'f';
                i++;
            }
            else{
                specs[*count][k++] = format[i];
            }
            specs[*count][k] = '\0';
            (*count)++;
        }
    }
}

//DETECT FORMATS...find string i.e. whatever inside ""
int extractFormat(char arr[], char format[]){
    int i = 0, k = 0;
    while (arr[i] && arr[i] != '\"') i++;
    if (!arr[i]) return 0;
    i++;

    while (arr[i] && arr[i] != '\"')
        format[k++] = arr[i++];

    format[k] = '\0';
    if (!arr[i]) return 0;
    return 1;
}

//DETECT ARGUMENT VARIABLE NAMES
void trim(char *str) {
    int start = 0, end = strlen(str) - 1;
    // remove leading spaces
    while (isspace(str[start])) start++;
    // remove trailing spaces and symbols
    while (end >= start && (isspace(str[end]) || str[end] == ')' || str[end] == ';'))
        end--;
    int k = 0;
    for (int i = start; i <= end; i++)
        str[k++] = str[i];
    str[k] = '\0';
}

void extractVariables(char arr[], char vars[][50], int *count) {
    *count = 0;
    int i = 0;
    // 🔹 Step 1: Skip till first quote
    while (arr[i] && arr[i] != '\"') i++;
    if (!arr[i]) return;
    i++;
    // 🔹 Step 2: Skip format string
    while (arr[i] && arr[i] != '\"') i++;
    if (!arr[i]) return;
    i++;

    char temp[200];
    int k = 0;

    int parenDepth = 0; // 🔥 key improvement
    // 🔹 Step 3: Parse arguments
    while (arr[i]) {
        if (arr[i] == '(') parenDepth++;
        if (arr[i] == ')') parenDepth--;
        // split only when comma is OUTSIDE parentheses
        if (arr[i] == ',' && parenDepth == 0) {
            temp[k] = '\0';
            trim(temp);
            if (strlen(temp) > 0) {
                strcpy(vars[*count], temp);
                (*count)++;
            }
            k = 0;
        }
        else {
            temp[k++] = arr[i];
        }
        i++;
    }
    // 🔹 Last argument
    temp[k] = '\0';
    trim(temp);

    if (strlen(temp) > 0) {
        strcpy(vars[*count], temp);
        (*count)++;
    }
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

//MATCH THE SPECIFIER WITH ITS TYPE
int matchType(char *spec, int varType){
    if (strcmp(spec, "%d") == 0 && varType == 0) return 1;
    if (strcmp(spec, "%f") == 0 && varType == 1) return 1;
    if (strcmp(spec, "%lf") == 0 && varType == 2) return 1;
    if (strcmp(spec, "%c") == 0 && varType == 3) return 1;
    if (strcmp(spec, "%s") == 0 && varType == 3) return 1;

    return 0;
}

//DETECTS PRINTF SCANF
void printscan(fileLine arr[], int size){
    for (int i = 0; i < size; i++){
        char *line = arr[i].lineText;

        if (strstr(line, "printf")){
            if (printcheck(line, arr[i].lineLen))
                printf("printf ERROR\n");
            else
                printf("printf OK\n");
        }

        if (strstr(line, "scanf")){
            if (scancheck(line, arr[i].lineLen))
                printf("scanf ERROR\n");
            else
                printf("scanf OK\n");
        }

        if (strstr(line, "fprintf")){
            if (fprintfcheck(line, arr[i].lineLen))
                printf("fprintf ERROR\n");
            else
                printf("fprintf OK\n");
        }

        if (strstr(line, "fscanf")){
            if (fscanfcheck(line, arr[i].lineLen))
                printf("fscanf ERROR\n");
            else
                printf("fscanf OK\n");
        }

        if (strstr(line, "gets")){
            if (getscheck(line, arr[i].lineLen))
                printf("gets ERROR\n");
            else
                printf("gets OK\n");
        }

        if (strstr(line, "puts")){
            if (putscheck(line, arr[i].lineLen))
                printf("puts ERROR\n");
            else
                printf("puts OK\n");
        }
    }
}

//DETECTS PRINTF
int printcheck(char arr[], int size){
    char format[200];
    if (!extractFormat(arr, format)) return 1;

    char specs[20][5];
    int specCount;
    extractSpecifiers(format, specs, &specCount);

    char vars[20][50];
    int varCount;
    extractVariables(arr, vars, &varCount);

    if (specCount != varCount) return 1;

    // printf should NOT have &
    for (int i = 0; i < varCount; i++){
        if (vars[i][0] == '&')
            return 1;
    }

    return 0;
}

//DETECTS SCANF
int scancheck(char arr[], int size){
    char format[200];
    if (!extractFormat(arr, format)) return 1;

    char specs[20][5];
    int specCount;
    extractSpecifiers(format, specs, &specCount);

    char vars[20][50];
    int varCount;
    extractVariables(arr, vars, &varCount);

    if (specCount != varCount) return 1;

    for (int i = 0; i < specCount; i++){
        // %s should NOT have &
        if (strcmp(specs[i], "%s") == 0 && vars[i][0] == '&')
            return 1;
        // others MUST have &
        if (strcmp(specs[i], "%s") != 0 && vars[i][0] != '&')
            return 1;
    }

    return 0;
}

//DETECTS FPRINTF
int fprintfcheck(char arr[], int size){
    return printcheck(arr, size);  // same logic
}

//DETECTS FSCANF
int fscanfcheck(char arr[], int size){
    return scancheck(arr, size);  // same logic
}

// GETS AND PUTS
int getscheck(char arr[], int size){
    char *p = strchr(arr, '(');
    if (!p) return 1;

    p++;
    while (*p == ' ' || *p == '\t') p++;

    // ❌ string literal
    if (*p == '\"') return 1;

    // extract variable
    char var[50];
    int k = 0;

    while (*p && *p != ')' && *p != ';')
        var[k++] = *p++;

    var[k] = '\0';

    // trim
    trim(var);

    // ❌ must be valid identifier (char array expected)
    if (!isalpha(var[0])) return 1;
    // ❌ reject single letter variables (likely int)
    if (strlen(var) == 1)
        return 1;

    return 0;
}

int putscheck(char arr[], int size){
    char *p = strchr(arr, '(');
    if (!p) return 1;

    p++;
    while (*p == ' ' || *p == '\t') p++;

    // puts can accept string literal OR variable
    if (*p == '\0') return 1;

    return 0;
}



//CHECK MAIN FUNCTION EXISTENCE
int is_main_line(char *line) {
    return strstr(line, "main(") != NULL;
}


// COUNT FUNCTIONS AND PROTOTYPES
void function_and_prototype_count(fileLine arr[], int len)
{
    const char *types[] = {"int", "char", "void", "double", "float", "long", "short"};
    int totalFunctions = 0;
    int totalPrototypes = 0;
    int mainLine = -1;

    // find main line
    for (int i = 0; i < len; i++) {
        if (strstr(arr[i].lineText, "main(")) {
            mainLine = i;
            break;
        }
    }

    for (int i = 0; i < len; i++) {
        char line[200];
        strcpy(line, arr[i].lineText);

        // remove leading spaces
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;

        if (strlen(ptr) == 0) continue;

        // must contain ()
        if (!(strchr(ptr, '(') && strchr(ptr, ')')))
            continue;

        // ignore control statements
        if (strstr(ptr, "for(") || strstr(ptr, "while(") ||
            strstr(ptr, "if(") || strstr(ptr, "switch("))
            continue;

        // extract first word
        char temp[200];
        strcpy(temp, ptr);
        char *token = strtok(temp, " \t(");

        int isType = 0;
        for (int t = 0; t < 7; t++) {
            if (token && strcmp(token, types[t]) == 0) {
                isType = 1;
                break;
            }
        }

        if (!isType) continue;

        // prototype
        // check if line ends with ';' (ignore spaces)
        int k = strlen(ptr) - 1;
        while (k >= 0 && (ptr[k] == ' ' || ptr[k] == '\t' || ptr[k] == '\n'))
            k--;
            
        if (k >= 0 && ptr[k] == ';') {
            if (i < mainLine)
                totalPrototypes++;
        }
        else {
            totalFunctions++;
        }
    }

    printf("Total Functions used including main: %d\n", totalFunctions);
    printf("Total Prototypes before main: %d\n", totalPrototypes);

    if (totalPrototypes < totalFunctions - 1)
        printf("Some prototypes are not defined\n");
    else
        printf("Prototypes are defined\n");
}


//COUNT VARIABLES
int getTypeIndex(char *word) {
    const char *types[] = {"int", "char", "long", "double", "float", "short"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(word, types[i]) == 0)
            return i;
    }
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

//🔥 FULL FLOW IN ONE LINE
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


//FOR LOOP CHECK
int isBalancedParentheses(char arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == '(') count++;
        else if (arr[i] == ')') count--;

        if (count < 0) return 0; // extra ')'
    }
    return count == 0;
}

int forcheck(char arr[], int size) {
    int semicolonCount = 0;
    int inSingleQuote = 0, inDoubleQuote = 0;

    for (int i = 0; i < size; i++) {
        // 🔹 Toggle quote states
        if (arr[i] == '\'' && !inDoubleQuote)
            inSingleQuote = !inSingleQuote;
        else if (arr[i] == '\"' && !inSingleQuote)
            inDoubleQuote = !inDoubleQuote;
        // 🔹 Count semicolons ONLY outside quotes
        else if (arr[i] == ';' && !inSingleQuote && !inDoubleQuote)
            semicolonCount++;
    }

    // 🔹 Conditions for valid for-loop
    if (semicolonCount != 2) return 1;
    if (inSingleQuote || inDoubleQuote) return 1;
    if (!isBalancedParentheses(arr, size)) return 1;

    return 0;
}

//WHILE LOOP CHECK
int whilecheck(char arr[], int size) {
    int inSingleQuote = 0, inDoubleQuote = 0;

    for (int i = 0; i < size; i++) {
        // 🔹 Toggle quotes
        if (arr[i] == '\'' && !inDoubleQuote)
            inSingleQuote = !inSingleQuote;
        else if (arr[i] == '\"' && !inSingleQuote)
            inDoubleQuote = !inDoubleQuote;
        // 🔹 Semicolon NOT allowed outside quotes
        else if (arr[i] == ';' && !inSingleQuote && !inDoubleQuote)
            return 1;
    }

    // 🔹 Final checks
    if (inSingleQuote || inDoubleQuote) return 1;
    if (!isBalancedParentheses(arr, size)) return 1;

    return 0;
}


//DETECT F CHECKS
typedef int (*checkFunc)(char[], int); //Define function pointer type

void fcheck(fileLine arr[], int len){
    char str[300], word[300];
    char keywords[8][10] = {
        "printf", "scanf", "gets", "puts",
        "fscanf", "fprintf", "for", "while"
    };
    // 🔹 Corresponding functions
    checkFunc functions[8] = {
        printcheck, scancheck, getscheck, putscheck,
        fscanfcheck, fprintfcheck, forcheck, whilecheck
    };

    for (int i = 0; i < len; i++){
        strcpy(str, arr[i].lineText);
        int k = 0;
        for (int j = 0; j <= arr[i].lineLen; j++){
            // 🔹 Word separator
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\t' || str[j] == '\0'){
                word[k] = '\0';
                if (k > 0){ // ignore empty words
                    // 🔹 Check against all keywords
                    for (int x = 0; x < 8; x++){
                        if (strcmp(word, keywords[x]) == 0 && strstr(str, word)){
                            int f = functions[x](str, arr[i].lineLen);
                            if (f)
                                printf("Error in Statement ---> line no: %d\n", arr[i].lineNo);
                            break; // stop after match
                        }
                    }
                }
                k = 0; // reset word
            }
            else{
                word[k++] = str[j];
            }
        }
    }
}


//DETECT UNDECLARED VARS
void undeclaredVariables(fileLine arr[], int len){
    char declared[200][50];
    int declCount = 0;
    char reportedGlobal[200][50];
    int globalCount = 0;
    const char *types[] = {"int","char","long","double","float","short"};
    const char *ignore[] = {
        "printf","scanf","gets","puts","return","for","while","if","else",
        "int","char","float","long","double","struct","void",
        "main","include"
    };
    int ignoreCount = 18;

    //STORE DECLARED VARIABLES
    for (int i = 0; i < len; i++) {
        char line[200];
        strcpy(line, arr[i].lineText);
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (strchr(ptr, '(') && strchr(ptr, ')')) continue;
        char temp[200];
        strcpy(temp, ptr);
        char *token = strtok(temp, " \t;");
        int isType = 0;
        for (int t = 0; t < 6; t++) {
            if (token && strcmp(token, types[t]) == 0) {
                isType = 1;
                break;
            }
        }
        if (!isType) continue;

        char *rest = strchr(ptr, ' ');
        if (!rest) continue;
        rest++;
        char vars[200];
        strcpy(vars, rest);
        char *var = strtok(vars, ",;");
        while (var != NULL) {
            while (*var == ' ' || *var == '\t') var++;
            char name[50];
            int k = 0;
            for (int j = 0; var[j] && var[j] != '=' && var[j] != '['; j++)
                name[k++] = var[j];
            name[k] = '\0';
            if (isalpha(name[0])) {
                strcpy(declared[declCount++], name);
            }
            var = strtok(NULL, ",;");
        }
    }

    //CHECK USAGE
    for (int i = 0; i < len; i++) {
        char line[200];
        strcpy(line, arr[i].lineText);
        char *token = strtok(line, " \t\n(){}[];,+-*/=<>!&|#\"");
        while (token != NULL) {
            if (!isalpha(token[0])) {
                token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|#\"");
                continue;
            }
            int skip = 0;
            for (int j = 0; j < ignoreCount; j++) {
                if (strcmp(token, ignore[j]) == 0) {
                    skip = 1;
                    break;
                }
            }
            if (strchr(token, '.')) skip = 1;
            char *pos = strstr(arr[i].lineText, token);
            if (pos && *(pos + strlen(token)) == '(')
                skip = 1;
            if (skip) {
                token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|#\"");
                continue;
            }
            int found = 0;
            for (int j = 0; j < declCount; j++) {
                if (strcmp(token, declared[j]) == 0) {
                    found = 1;
                    break;
                }
            }

            //CHECK GLOBAL DUPLICATE
            int alreadyGlobal = 0;
            for (int g = 0; g < globalCount; g++) {
                if (strcmp(reportedGlobal[g], token) == 0) {
                    alreadyGlobal = 1;
                    break;
                }
            }
            if (!found && !alreadyGlobal) {
                printf("Line %d: %s is undeclared\n", arr[i].lineNo, token);
                strcpy(reportedGlobal[globalCount++], token);
            }
            token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|#\"");
        }
    }
}


//DETECT DUPLICATE DECLARED VARS
void duplicateVariables(fileLine *arr, int len){
    const char *types[] = {"int","char","long","double","float","short"};
    char scopeVars[200][50];
    int scopeCount = 0;
    int braceCount = 0;

    for (int i = 0; i < len; i++){
        char line[200];
        strcpy(line, arr[i].lineText);
        // update scope using {}
        for (int j = 0; line[j]; j++) {
            if (line[j] == '{') {
                braceCount++;
                scopeCount = 0;   //NEW SCOPE → reset
            }
            else if (line[j] == '}') {
                braceCount--;
                scopeCount = 0;   //EXIT SCOPE → reset
            }
        }
        //ignore outside any scope
        if (braceCount <= 0) continue;
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (strlen(ptr) == 0) continue;

        // skip function headers
        if (strchr(ptr, '(') && strchr(ptr, ')') && strchr(ptr, '{') == NULL)
            continue;
        // check datatype
        char temp[200];
        strcpy(temp, ptr);
        char *token = strtok(temp, " \t;");
        int isType = 0;
        for (int t = 0; t < 6; t++) {
            if (token && strcmp(token, types[t]) == 0) {
                isType = 1;
                break;
            }
        }
        if (!isType) continue;

        // extract variables
        char *rest = strchr(ptr, ' ');
        if (!rest) continue;
        rest++;
        char vars[200];
        strcpy(vars, rest);
        char *var = strtok(vars, ",;");
        while (var != NULL){
            while (*var == ' ' || *var == '\t') var++;
            char name[50];
            int k = 0;
            for (int j = 0; var[j] && var[j] != '=' && var[j] != '['; j++)
                name[k++] = var[j];
            name[k] = '\0';
            if (!isalpha(name[0])) {
                var = strtok(NULL, ",;");
                continue;
            }
            // check duplicate in SAME SCOPE
            for (int j = 0; j < scopeCount; j++) {
                if (strcmp(scopeVars[j], name) == 0) {
                    printf("Line %d: Duplicate variable '%s'\n", arr[i].lineNo, name);
                    break;
                }
            }
            strcpy(scopeVars[scopeCount++], name);
            var = strtok(NULL, ",;");
        }
    }
}
