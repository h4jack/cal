# Expression Calculator

This project is a simple expression calculator implemented in C. It provides functionalities to convert infix expressions to postfix notation and evaluate the resulting postfix expressions.

## Project Structure

The project directory contains the following files:

- `cal.exe`: Executable file for the expression calculator.
- `expression-calculator-onefile.c`: Main source file containing the implementation of the expression calculator.
- `expression_calculator.c`: Source file containing functions for converting infix expressions to postfix notation and evaluating postfix expressions.
- `list.h`: Header file containing the implementation of a linked list data structure.
- `util.h`: Header file containing utility functions and definitions used in the project.

## Installation
To run the game, follow these steps:

#### Clone the repo and use and analyze the code:
```bash
git clone https://www.github.com/h4jack/cal.git ./Expressioin-Calculator
```
#### Navigate to the project directory:
```bash
cd Expressioin-Calculator
```
#### Run the game:
```bash
./cal.exe
```
## Usage

To use the expression calculator, you can compile the source files using a C compiler and then run the executable. Here's how to use it:

- Compile the source files:
```cmd
gcc expression-calculator-onefile.c expression_calculator.c -o cal.exe
```
- Run the executable:
```cmd
./cal.exe
```
- You will be prompted to enter an infix expression. You can also pass the expression as command-line arguments, e.g.:
```cmd
cal ./cal.exe "10*(-13+17)/1.5-17"
```

- The calculator will convert the infix expression to postfix notation, evaluate the postfix expression, and display the result.


## Documentation

For detailed documentation of the code and its functionalities, refer to the [Documentation.md](https://github.com/h4jack/cal/blob/main/Documentation.md) file.

## Expression Calculator Features

The expression calculator project provides the following features:

### Infix to Postfix Conversion

- Convert infix expressions to postfix notation.
- Supports arithmetic operators: addition (+), subtraction (-), multiplication (*), division (/), modulus (%), and exponentiation (^).
- Handles parentheses to determine the order of operations.

### Postfix Expression Evaluation

- Evaluate postfix expressions using a stack-based approach.
- Support for basic arithmetic operations and precedence rules.

### Error Handling

- Detects and handles various types of errors in input expressions.
- Error messages are displayed for informative purposes, including:
  - Invalid expressions.
  - Division by zero.
  - Unmatched parentheses.

### Command-Line Interface

- Accepts infix expressions as command-line arguments.
- Provides a user-friendly interface for entering infix expressions if no arguments are provided.
- Optional verbose mode (`-v` or `-V`) for displaying the input infix expression and the resulting postfix expression.

### Modular Design

- Organized into multiple source files for clarity and maintainability:
  - `expression-calculator-onefile.c`: Main entry point and command-line argument processing.
  - `expression_calculator.c`: Core functionality for expression conversion and evaluation.
  - `list.h`: Implementation of a linked list data structure.
  - `util.h`: Utility functions and definitions used throughout the project.

### Portable and Easy to Use

- Written in C for portability across different platforms.
- Simple compilation and execution process for ease of use.

## Authors

- [@h4jack](https://www.github.com/h4jack)


## License

This project is licensed under the [MIT License](https://github.com/h4jack/cal/blob/main/LICENSE/)


## Feedback

If you have any feedback or suggestions, please feel free to [create an issue](https://github.com/h4jack/cal/issues) or [contact us](https://github.com/h4jack).