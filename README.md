# 🚀 C Static Code Analyzer (Syntax Checker) v2.0

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Active-success.svg)
![Version](https://img.shields.io/badge/Version-2.0-orange.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

A powerful **C-based static code analysis tool** that reads a C source file and performs advanced **syntax checking, structural validation, and code analysis**.

This project goes beyond basic parsing and implements **compiler-like logic**, including **comment removal, tokenization, scope tracking, and format validation**.

🚀 This is an improved version of the project with enhanced parsing, 
better syntax validation, and advanced error detection.

---

## ✨ Highlights

- 🚀 Improved version with advanced parsing techniques  
- 🧠 Implements **mini-compiler level logic**  
- 🔍 Detects real-world coding mistakes  
- 🧩 Modular and scalable design  
- 💡 Strong focus on **clean code analysis**

---

## 🧠 Features

### 🔹 Code Preprocessing
- Removes single-line (`//`) and multi-line (`/* */`) comments
- Eliminates blank and unnecessary lines
- Generates **clean processed code**

---

### 🔹 Code Analysis
- Counts total valid lines of code
- Detects **C keywords with line numbers**
- Counts **built-in functions (with frequency)**
- Detects **functions and validates prototypes**

---

### 🔹 Variable Analysis
- Counts variables by data type:
  - `int`, `char`, `float`, `double`, `long`, `short`
- Supports **arrays**
- Calculates **memory usage**
- Detects:
  - ❌ Undeclared variables
  - ⚠️ Duplicate variables (scope-based)

---

### 🔹 Syntax Validation
Advanced validation for:
- `printf`, `scanf`
- `fprintf`, `fscanf`
- `gets`, `puts`

Checks include:
- ✔️ Format specifier vs argument matching  
- ✔️ Correct use of `&` in `scanf`  
- ✔️ Invalid usage detection  

---

### 🔹 Structural Checks
- Stack-based bracket validation:
  - `{ }`, `( )`, `[ ]`
- Detects:
  - ❌ Unmatched brackets  
  - ❌ Mismatched pairs  
- Ignores brackets inside strings ✅

---

### 🔹 Control Structure Validation
- Validates `for` loop syntax:
  - Ensures correct number of `;`
  - Checks balanced parentheses
- Validates `while` loop syntax

---

### 🔹 Output
- Prints **cleaned and analyzed code**
- Writes formatted output to: output.txt

  
---

## 🏗️ Project Structure
syntax-checker/

├── main.c

├── input.txt

├── output.txt

└── README.md



| File | Description |
|------|------------|
| `main.c` | Main analyzer program |
| `input.txt` | Input C program |
| `output.txt` | Generated formatted output |

---

## ⚙️ How It Works

1. Reads C file **line-by-line**
2. Removes comments and cleans code
3. Stores lines using structured format
4. Applies multiple analysis modules:
   - Keyword detection
   - Syntax validation
   - Variable tracking
   - Function analysis
5. Outputs results to console + file

---

## 🧪 Example Output
------ CLEAN CODE ------

Line 1 [18]: #include<stdio.h>

Line 2 [11]: int main()

------ BRACKET CHECK ------

All brackets are balanced correctly ✅

------ KEYWORDS ------

Line 2: int

------ BUILTIN FUNCTIONS ------

printf: 2

------ UNDECLARED VARIABLE CHECK ------

Line 8: x is undeclared

------ DUPLICATE VARIABLE CHECK ------

Line 11: Duplicate variable 'a'


---

## 🛠️ Technologies Used

### 💻 Language
- C

### 📚 Concepts
- File Handling
- Structures
- String Parsing
- Tokenization (`strtok`)
- Pointers & Memory Management
- Stack Implementation
- Function Pointers
- Static Code Analysis

---

## 🔄 Changelog

### 🚀 Version 2.0 (Latest)
- Added comment removal (`//`, `/* */`)
- Implemented undeclared variable detection
- Added duplicate variable detection (scope-aware)
- Improved `printf/scanf` validation using format specifiers
- Stack-based bracket matching
- Advanced variable counting (arrays + memory)
- Token-based parsing (`strtok`)
- Function pointer-based validation system

### 🟢 Version 1.0
- Basic syntax checker
- Keyword detection
- Simple bracket matching
- Basic variable and function counting

---

## 🔮 Future Improvements

- Support nested scopes more accurately
- Detect unused variables
- Perform type checking across assignments
- Multi-file analysis support
- GUI or Web-based interface

---

## 👨‍💻 Author

**Khushpreet Kaur**  
Computer Science Student  

🔗 GitHub: https://github.com/KhushpreetKaur10

---

## ⭐ If you like this project

Give it a ⭐ on GitHub and feel free to contribute!
