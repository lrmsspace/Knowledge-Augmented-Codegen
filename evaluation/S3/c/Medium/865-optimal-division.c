// Source: https://leetcode.com/problems/optimal-division/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The adjacent integers in nums will perform the float division.
//
//
// 	For example, for nums = [2,3,4], we will evaluate the expression "2/3/4".
//
//
// However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.
//
// Return the corresponding expression that has the maximum value in string format.
//
// Note: your expression should not contain redundant parenthesis.
//
// Example:
// Input: nums = [1000,100,10,2]
// Output: "1000/(100/10/2)"
// Explanation: 1000/(100/10/2) = 1000/((100/10)/2) = 200
// However, the bold parenthesis in "1000/((100/10)/2)" are redundant since they do not influence the operation priority.
// So you should return "1000/(100/10/2)".
// Other cases:
// 1000/(100/10)/2 = 50
// 1000/(100/(10/2)) = 50
// 1000/100/10/2 = 0.5
// 1000/100/(10/2) = 2
//
// Constraints:
// 1 <= nums.length <= 10
// 	2 <= nums[i] <= 1000
// 	There is only one optimal division for the given input.
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

char* optimalDivision(int* nums, int numsSize) {
    // If there's only one number, return it as a string.
    if (numsSize == 1) {
        char* result = (char*)malloc(12); // Enough for "1000\0"
        sprintf(result, "%d", nums[0]);
        return result;
    }

    // Start building the result string with the first number.
    char* result = (char*)malloc(1024); // Allocate enough memory for the result.
    sprintf(result, "%d", nums[0]);

    // If there are two numbers, just return "a/b".
    if (numsSize == 2) {
        sprintf(result + strlen(result), "/%d", nums[1]);
        return result;
    }

    // For more than two numbers, we want to maximize the division by grouping the last n-1 numbers together.
    sprintf(result + strlen(result), "/(");
    for (int i = 1; i < numsSize; i++) {
        sprintf(result + strlen(result), "%d", nums[i]);
        if (i < numsSize - 1) {
            sprintf(result + strlen(result), "/");
        }
    }
    sprintf(result + strlen(result), ")");

    return result;      
}
