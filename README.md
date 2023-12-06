# Compiler Project

This is a custom compiler for C Minus language, featuring a table-driven lexer, Bison parser, and semantic analysis. It's designed for efficient parsing and semantic analysis of C Minus programs.

## Features

- Table-Driven Lexer
- Bison Parser
- Semantic Analysis

## Prerequisites

- GNU Bison
- GNU Make
- GCC (GNU Compiler Collection)

## Compiling the Compiler

1. To clean previous builds and prepare for a fresh compile:
   ```bash
   make clean
   ```
2. To generate Bison parser files:
   ```bash
   make bison
   ```
3. To compile the entire project:
   ```bash
   make all
   ```

## Running Tests

To run tests:
```bash
make tests
```

## Usage

Compile a C Minus source file using:
```bash
bin/cmc path/to/source.cminus
```

Replace `path/to/source.cminus` with the actual path to your C Minus source file.
