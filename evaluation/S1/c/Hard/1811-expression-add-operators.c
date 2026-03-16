// Source: https://leetcode.com/problems/expression-add-operators/   |   Difficulty: Hard
//
// Problem Description:
// Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.
//
// Note that operands in the returned expressions should not contain leading zeros.
//
// Note that a number can contain multiple digits.
//
// Example:
// Input: num = "123", target = 6
// Output: ["1*2*3","1+2+3"]
// Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
//
// Constraints:
// 1 <= num.length <= 10
// 	num consists of only digits.
// 	-231 <= target <= 231 - 1
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Expression parsing (stack, simulation)
//   • When to use: When evaluating or converting arithmetic or logical expressions involving various operators, including unary and binary, and handling different associativities. It's useful for implementing calculators or compilers.
//   • Idea: This technique involves using stacks to parse and evaluate expressions, correctly handling operator precedence and associativity, including unary and right-associative operators. It typically processes expressions in O(N) time, where N is the expression length.
//   • Invariants: The operator stack always maintains operators in increasing order of precedence from bottom to top (excluding parentheses).; When processing an operand, it is immediately pushed onto the operand stack.
//   • Tips: Distinguish unary from binary operators based on context (e.g., preceding token).; Assign higher precedence to unary operators than most binary ones.
//   • Pitfalls: Incorrectly identifying unary vs. binary operators based on context.; Failing to correctly implement operator precedence rules.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** addOperators(char* num, int target, int* returnSize) {
    int numLen = strlen(num);
    char** results = (char**)malloc(10000 * sizeof(char*)); // Allocate space for results
    *returnSize = 0;
    
    void backtrack(int index, long long prevOperand, long long currentValue, char* expression, int exprLen) {
        if (index == numLen) {
            if (currentValue == target) {
                expression[exprLen] = '\0';
                results[*returnSize] = (char*)malloc((exprLen + 1) * sizeof(char));
                strcpy(results[*returnSize], expression);
                (*returnSize)++;
            }
            return;
        }
        
        long long operand = 0;
        int operandStart = index;
        for (int i = index; i < numLen; i++) {
            if (i > index && num[operandStart] == '0') break; // Leading zero check
            
            operand = operand * 10 + (num[i] - '0');
            int operandLen = i - operandStart + 1;
            
            if (index == 0) {
                // First operand, no operator
                memcpy(expression + exprLen, num + operandStart, operandLen);
                backtrack(i + 1, operand, operand, expression, exprLen + operandLen);
            } else {
                // Addition
                expression[exprLen] = '+';
                memcpy(expression + exprLen + 1, num + operandStart, operandLen);
                backtrack(i + 1, operand, currentValue + operand, expression, exprLen + 1 + operandLen);
                
                // Subtraction
                expression[exprLen] = '-';
                memcpy(expression + exprLen + 1, num + operandStart, operandLen);
                backtrack(i + 1, -operand, currentValue - operand, expression, exprLen + 1 + operandLen);
                
                // Multiplication
                expression[exprLen] = '*';
                memcpy(expression + exprLen + 1, num + operandStart, operandLen);
                backtrack(i + 1, prevOperand * operand,
                          currentValue - prevOperand + (prevOperand * operand),
                          expression, exprLen + 1 + operandLen);
            }
        }
    }
    
    char* expression = (char*)malloc(2 * numLen * sizeof(char)); // Max size for expression
    backtrack(0, 0, 0, expression, 0);
    free(expression);
    return results;
}
