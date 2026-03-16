// Source: https://leetcode.com/problems/decode-string/   |   Difficulty: Medium
//
// Problem Description:
// Given an encoded string, return its decoded string.
//
// The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
//
// You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
//
// The test cases are generated so that the length of the output will never exceed 105.
//
// Example:
// Input: s = "3[a]2[bc]"
// Output: "aaabcbc"
//
// Constraints:
// 1 <= s.length <= 30
// 	s consists of lowercase English letters, digits, and square brackets '[]'.
// 	s is guaranteed to be a valid input.
// 	All the integers in s are in the range [1, 300].
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* decodeString(char* s) {
    int n = strlen(s);
    char* stack[n];
    int top = -1;

    for (int i = 0; i < n; i++) {
        if (s[i] != ']') {
            stack[++top] = &s[i];
        } else {
            // Pop until we find the matching '['
            char* substr[100]; // Assuming max substring length is 100
            int substr_len = 0;
            while (top >= 0 && *stack[top] != '[') {
                substr[substr_len++] = stack[top--];
            }
            top--; // Pop the '['

            // Now we need to find the number before the '['
            char num_str[10]; // Assuming max number length is 10
            int num_len = 0;
            while (top >= 0 && isdigit(*stack[top])) {
                num_str[num_len++] = *stack[top--];
            }
            num_str[num_len] = '\0';
            int k = atoi(num_str);

            // Reverse the substring
            for (int j = 0; j < substr_len / 2; j++) {
                char* temp = substr[j];
                substr[j] = substr[substr_len - j - 1];
                substr[substr_len - j - 1] = temp;
            }

            // Push the repeated substring back to stack
            for (int j = 0; j < k; j++) {
                for (int m = 0; m < substr_len; m++) {
                    stack[++top] = substr[m];
                }
            }
        }
    }

    // Construct the final result from the stack
    char* result = malloc((top + 2) * sizeof(char)); // +1 for null terminator
    int idx = 0;
    for (int i = 0; i <= top; i++) {
        result[idx++] = *stack[i];
    }
    result[idx] = '\0';

    return result;      
}
