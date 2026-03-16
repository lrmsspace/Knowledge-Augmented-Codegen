// Source: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/   |   Difficulty: Medium
//
// Problem Description:
// A parentheses string is valid if and only if:
//
//
// 	It is the empty string,
// 	It can be written as AB (A concatenated with B), where A and B are valid strings, or
// 	It can be written as (A), where A is a valid string.
//
//
// You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.
//
//
// 	For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
//
//
// Return the minimum number of moves required to make s valid.
//
// Example:
// Input: s = "())"
// Output: 1
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '(' or ')'.
//
// Helpful references (internal KB):
// - Balanced bracket sequences (number, counting)
//   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
//   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
//   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
//   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
//   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
// - Balanced bracket sequences (number, counting)
//   • When to use: When asked to count the total number of valid or well-formed bracket sequences of a certain length or with a specific number of pairs. This often involves combinatorial reasoning or dynamic programming.
//   • Idea: Counts the total number of valid bracket sequences of a given length or with a specific number of pairs, where each opening bracket has a corresponding closing bracket. This problem often has a combinatorial solution, typically involving Catalan numbers, with a time complexity of O(N) or O(N^2) for DP.
//   • Invariants: At any prefix of the sequence, the number of open brackets is greater than or equal to the number of closing brackets.; The total number of open brackets in the sequence equals the total number of closing brackets.
//   • Tips: Recognize the pattern for Catalan numbers if applicable.; Dynamic programming can be used for more complex variations.
//   • Pitfalls: Incorrectly handling the balance constraint (open count >= close count).; Overcounting or undercounting sequences.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minAddToMakeValid(char* s) {
    int balance = 0; // Tracks the number of unmatched '('
    int insertions = 0; // Counts the number of insertions needed

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            balance++; // Found an opening parenthesis, increase balance
        } else { // s[i] == ')'
            if (balance > 0) {
                balance--; // Found a matching pair, decrease balance
            } else {
                insertions++; // No matching '(', need to insert one
            }
        }
    }

    // Any remaining unmatched '(' will require an insertion of ')'
    return insertions + balance;        
}
