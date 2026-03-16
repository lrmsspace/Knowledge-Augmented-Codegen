// Source: https://leetcode.com/problems/maximum-score-after-splitting-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s of zeros and ones, return the maximum score after splitting the string into two non-empty substrings (i.e. left substring and right substring).
//
// The score after splitting a string is the number of zeros in the left substring plus the number of ones in the right substring.
//
// Example:
// Input: s = "011101"
// Output: 5 
// Explanation: 
// All possible ways of splitting s into two non-empty substrings are:
// left = "0" and right = "11101", score = 1 + 4 = 5 
// left = "01" and right = "1101", score = 1 + 3 = 4 
// left = "011" and right = "101", score = 1 + 2 = 3 
// left = "0111" and right = "01", score = 1 + 1 = 2 
// left = "01110" and right = "1", score = 2 + 1 = 3
//
// Constraints:
// 2 <= s.length <= 500
// 	The string s consists of characters '0' and '1' only.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Suffix Automaton (graph, string, counting)
//   • When to use: Use when processing all suffixes or substrings of a string, especially for tasks requiring counting distinct substrings or efficient pattern matching. It is particularly useful for incremental string construction.
//   • Idea: The Suffix Automaton is a directed acyclic graph that represents all distinct substrings of a given string. It has a linear number of states and transitions, allowing for efficient string processing in O(N) time complexity for construction.
//   • Invariants: The automaton correctly represents all distinct substrings of the string processed up to the current character.; Each state corresponds to an equivalence class of substrings sharing the same end positions.
//   • Tips: Mark terminal states by traversing suffix links from the state representing the full string.; The `last` pointer always tracks the state for the entire string processed.
//   • Pitfalls: Incorrectly handling the three cases for adding a new character can lead to an invalid automaton.; Forgetting to update the `last` state after each character addition breaks incremental construction.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxScore(char* s) {
    int n = 0;
    int totalOnes = 0;
    int maxScore = 0;

    // First, count the total number of '1's in the string
    for (char* p = s; *p != '\0'; p++) {
        if (*p == '1') {
            totalOnes++;
        }
        n++;
    }

    int leftZeros = 0;
    int rightOnes = totalOnes;

    // Iterate through the string to find the maximum score
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == '0') {
            leftZeros++;
        } else {
            rightOnes--;
        }
        int currentScore = leftZeros + rightOnes;
        if (currentScore > maxScore) {
            maxScore = currentScore;
        }
    }

    return maxScore;        
}
