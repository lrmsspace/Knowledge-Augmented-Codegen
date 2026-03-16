// Source: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string s of even length n. The string consists of exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.
//
// A string is called balanced if and only if:
//
//
// 	It is the empty string, or
// 	It can be written as AB, where both A and B are balanced strings, or
// 	It can be written as [C], where C is a balanced string.
//
//
// You may swap the brackets at any two indices any number of times.
//
// Return the minimum number of swaps to make s balanced.
//
// Example:
// Input: s = "][]["
// Output: 1
// Explanation: You can make the string balanced by swapping index 0 with index 3.
// The resulting string is "[[]]".
//
// Constraints:
// n == s.length
// 	2 <= n <= 106
// 	n is even.
// 	s[i] is either '[' or ']'.
// 	The number of opening brackets '[' equals n / 2, and the number of closing brackets ']' equals n / 2.
//
// Helpful references (internal KB):
// - Balanced bracket sequences (number, counting)
//   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
//   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
//   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
//   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
//   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
// - Balanced bracket sequences (number, counting)
//   • When to use: Use when the problem asks for the total number of valid arrangements of opening and closing brackets, ensuring all pairs are matched and correctly nested. It applies to combinatorial problems requiring structured pairing.
//   • Idea: This technique counts the number of ways to form sequences of opening and closing brackets such that they are balanced and properly nested. It is a classic combinatorial problem, typically solved in O(N) or O(N^2) time.
//   • Invariants: At any point in sequence construction, the count of open brackets placed must be greater than or equal to the count of closed brackets placed.; The total number of open brackets in a complete valid sequence must exactly equal the total number of closed brackets.
//   • Tips: Recognize the connection to Catalan numbers for common variations (e.g., N pairs of parentheses).; Dynamic programming can solve more complex variations with different bracket types or constraints.
//   • Pitfalls: Forgetting the 'prefix sum' condition: the count of open brackets must always be greater than or equal to close brackets at any point.; Incorrectly applying Catalan numbers to problems with additional constraints or different bracket types.
// - Balanced bracket sequences (number, counting)
//   • When to use: When asked to count the total number of valid or well-formed bracket sequences of a certain length or with a specific number of pairs. This often involves combinatorial reasoning or dynamic programming.
//   • Idea: Counts the total number of valid bracket sequences of a given length or with a specific number of pairs, where each opening bracket has a corresponding closing bracket. This problem often has a combinatorial solution, typically involving Catalan numbers, with a time complexity of O(N) or O(N^2) for DP.
//   • Invariants: At any prefix of the sequence, the number of open brackets is greater than or equal to the number of closing brackets.; The total number of open brackets in the sequence equals the total number of closing brackets.
//   • Tips: Recognize the pattern for Catalan numbers if applicable.; Dynamic programming can be used for more complex variations.
//   • Pitfalls: Incorrectly handling the balance constraint (open count >= close count).; Overcounting or undercounting sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var minSwaps = function(s) {
    let balance = 0; // Current balance of brackets
    let maxBalance = 0; // Maximum balance encountered
    
    for (const char of s) {
        if (char === '[') {
            balance++;
        } else {
            balance--;
        }
        maxBalance = Math.max(maxBalance, balance);
    }
    
    // The number of swaps needed is half of the maximum imbalance
    return Math.ceil(maxBalance / 2);
};
