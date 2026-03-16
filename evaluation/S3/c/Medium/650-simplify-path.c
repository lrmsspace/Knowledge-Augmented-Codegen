// Source: https://leetcode.com/problems/simplify-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given an absolute path for a Unix-style file system, which always begins with a slash '/'. Your task is to transform this absolute path into its simplified canonical path.
//
// The rules of a Unix-style file system are as follows:
//
//
// 	A single period '.' represents the current directory.
// 	A double period '..' represents the previous/parent directory.
// 	Multiple consecutive slashes such as '//' and '///' are treated as a single slash '/'.
// 	Any sequence of periods that does not match the rules above should be treated as a valid directory or file name. For example, '...' and '....' are valid directory or file names.
//
//
// The simplified canonical path should follow these rules:
//
//
// 	The path must start with a single slash '/'.
// 	Directories within the path must be separated by exactly one slash '/'.
// 	The path must not end with a slash '/', unless it is the root directory.
// 	The path must not have any single or double periods ('.' and '..') used to denote current or parent directories.
//
//
// Return the simplified canonical path.
//
// Example:
// Input: path = "/home/"
//
// Output: "/home"
//
// Explanation:
//
// The trailing slash should be removed.
//
// Constraints:
// 1 <= path.length <= 3000
// 	path consists of English letters, digits, period '.', slash '/' or '_'.
// 	path is a valid absolute Unix path.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Expression parsing (stack, simulation)
//   • When to use: When evaluating or converting arithmetic or logical expressions involving various operators, including unary and binary, and handling different associativities. It's useful for implementing calculators or compilers.
//   • Idea: This technique involves using stacks to parse and evaluate expressions, correctly handling operator precedence and associativity, including unary and right-associative operators. It typically processes expressions in O(N) time, where N is the expression length.
//   • Invariants: The operator stack always maintains operators in increasing order of precedence from bottom to top (excluding parentheses).; When processing an operand, it is immediately pushed onto the operand stack.
//   • Tips: Distinguish unary from binary operators based on context (e.g., preceding token).; Assign higher precedence to unary operators than most binary ones.
//   • Pitfalls: Incorrectly identifying unary vs. binary operators based on context.; Failing to correctly implement operator precedence rules.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* simplifyPath(char* path) {
    char* stack[3000]; // Stack to hold directory names
    int top = -1; // Stack pointer

    char* token = strtok(path, "/"); // Split the path by '/'
    while (token != NULL) {
        if (strcmp(token, ".") == 0) {
            // Current directory, do nothing
        } else if (strcmp(token, "..") == 0) {
            // Parent directory, pop from stack if not empty
            if (top >= 0) {
                top--;
            }
        } else {
            // Valid directory name, push onto stack
            stack[++top] = token;
        }
        token = strtok(NULL, "/"); // Get next token
    }

    // Build the simplified path
    char* result = (char*)malloc(3000 * sizeof(char));
    result[0] = '\0'; // Initialize result as empty string

    for (int i = 0; i <= top; i++) {
        strcat(result, "/");
        strcat(result, stack[i]);
    }

    // If the result is empty, it means we are at the root directory
    return strlen(result) > 0 ? result : "/";       
}
