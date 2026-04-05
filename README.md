# 🚀 C Static Code Analyzer (Syntax Checker) v2.0

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Active-success.svg)
![Version](https://img.shields.io/badge/Version-2.0-orange.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

A powerful **C-based static code analysis tool** that reads a C source file and performs advanced **syntax checking, structural validation, and code analysis**.
This project goes beyond basic parsing and implements **compiler-like logic**, including **comment removal, tokenization, scope tracking, and format validation**.

This project is an improved version that highlights strong understanding of low-level programming in C, including memory management, pointer operations, and efficient data processing with modular design.

---

## ✨ Highlights

- 🚀 Modular multi-file architecture (industry-style design)
- 🧠 Compiler-inspired architecture (Parser + Validator separation)
- 🧩 Scalable and extensible codebase
- 🧪 Includes unit testing for core components
- ⚡ Efficient string parsing and memory handling
- 🚀 Improved version with advanced parsing techniques  
- 🧠 Implements **mini-compiler level logic**  
- 🔍 Detects real-world coding mistakes  
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

## 🧪 Testing

Basic unit tests are included for core modules:

- `test_parser.c` → Tests parsing logic  
- `test_validator.c` → Tests validation rules  
- `test_runner.c` → Runs all test cases  

Run tests by compiling:
```bash
gcc tests/*.c src/*.c -Iinclude -o tests
./tests
```
---

## 🏗️ Project Structure

> 📌 Each module follows separation of concerns with a clearly defined responsibility.

```
c-static-code-analyzer/
│
├── main.c
│
├── include/                  # Header files (.h)
│   ├── cleaner.h
│   ├── file_handler.h
│   ├── keyword.h
│   ├── bracket.h
│   ├── builtin.h
│   ├── function.h
│   ├── variables.h
│   ├── parser.h
│   ├── validator.h
│   ├── syntax.h
│   ├── undeclared.h
│   └── duplicate.h
│
├── src/                      # Implementation files (.c)
│   ├── cleaner.c
│   ├── file_handler.c
│   ├── keyword.c
│   ├── bracket.c
│   ├── builtin.c
│   ├── function.c
│   ├── variables.c
│   ├── parser.c
│   ├── validator.c
│   ├── syntax.c
│   ├── undeclared.c
│   └── duplicate.c
│
├── models/
│   └── fileline.h
│
├── tests/
│   ├── test_parser.c
│   ├── test_validator.c
│   └── test_runner.c
│
├── utils/
│   ├── helpers.c
│   └── helpers.h
│
├── input.txt
├── output.txt
└── Makefile
```



---

## 📊 Key Modules Overview

| File | Description |
|------|------------|
| `main.c` | Entry point; orchestrates all modules and controls execution flow |
| `file_handler.c` | Handles file reading and writing |
| `cleaner.c` | Removes comments and stores clean code |
| `keyword.c` | Identifies C keywords |
| `bracket.c` | Checks bracket balancing |
| `builtin.c` | Counts built-in functions |
| `function.c` | Counts functions and prototypes |
| `variables.c` | Counts variables and calculates memory |
| `parser.c` | Parses format strings and extracts components |
| `validator.c` | Validates I/O functions and syntax rules |
| `syntax.c` | Checks loop syntax (`for`, `while`) |
| `undeclared.c` | Finds undeclared variables |
| `duplicate.c` | Detects duplicate variable declarations |
| `input.txt` | Input C source file |
| `output.txt` | Output of analyzed code |
| `Makefile` | Build automation script |

---

## 🧩 Architecture

This project follows a **modular, layered design** inspired by compiler architecture.

### 🔹 Key Design Principles
- Separation of Concerns
- Modular Components
- Reusable Parsing Logic
- Scalable Structure

### 🔹 Parser vs Validator (Important Design Choice)

- **Parser** → Extracts structured data from raw code  
- **Validator** → Applies rules and detects errors  

This separation improves:
- Maintainability  
- Testability  
- Reusability  

---
## 🧭 Architecture Flow
```
Input C Code
│
▼
[ Cleaner ]
│
▼
[ Parser ] ───► Extract Format / Variables
│
▼
[ Validator ] ───► Check printf/scanf, syntax
│
▼
[ Analyzer Modules ]
│
▼
Output (Console + File)
```
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
```
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
```

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
- Modular multi-file architecture
- Compiler-inspired design (parser + validator separation)
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

## 💡 Why This Project?

This project simulates the **front-end of a compiler**, focusing on:

- Lexical-level parsing
- Syntax validation
- Static code analysis

It demonstrates strong understanding of:
- Parsing techniques
- Code analysis strategies
- Modular system design
- Low-level memory handling and pointer-based operations in C

---
## ▶️ How to Run

> ⚠️ Requires `gcc` installed (Linux / macOS / Windows with MinGW)

---

## 🔹 Method 1: Using Makefile (Recommended)

### 1. Clone the Repository

```bash
git clone https://github.com/KhushpreetKaur10/c-static-code-analyzer.git
cd c-static-code-analyzer
```

### 2. Build the Project

```bash
make
```

### 3. Add Input File

Place your C source code inside:

```
input.txt
```

### 4. Run the Analyzer

```bash
make run
```

### 5. View Output

* Console → Displays analysis results
* File → Output saved in:

```
output.txt
```

### 6. Run Tests (Optional)

```bash
make test
```

### 7. Clean Build Files

```bash
make clean
```

---

## 🔹 Method 2: Manual Compilation

### 1. Compile the Project

```bash
gcc src/*.c main.c -Iinclude -o analyzer
```

### 2. Run the Program

```bash
./analyzer
```

### 3. Run Tests (Optional)

```bash
gcc tests/*.c src/*.c -Iinclude -o tests
./tests
```

---

## 💡 Tip

Using the **Makefile** is recommended for easier builds and better project management as the project grows.

---


## 👨‍💻 Author

**Khushpreet Kaur**  
Computer Science Student  

🔗 GitHub: https://github.com/KhushpreetKaur10

---

## ⭐ If you like this project

Give it a ⭐ on GitHub and feel free to contribute!
