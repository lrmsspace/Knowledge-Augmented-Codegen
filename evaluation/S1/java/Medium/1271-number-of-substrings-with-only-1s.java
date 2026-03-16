// Source: https://leetcode.com/problems/number-of-substrings-with-only-1s/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, return the number of substrings with all characters 1's. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "0110111"
// Output: 9
// Explanation: There are 9 substring in total with only 1's characters.
// "1" -> 5 times.
// "11" -> 3 times.
// "111" -> 1 time.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Suffix Automaton (graph, string, counting)
//   • When to use: Use when processing all suffixes or substrings of a string, especially for tasks requiring counting distinct substrings or efficient pattern matching. It is particularly useful for incremental string construction.
//   • Idea: The Suffix Automaton is a directed acyclic graph that represents all distinct substrings of a given string. It has a linear number of states and transitions, allowing for efficient string processing in O(N) time complexity for construction.
//   • Invariants: The automaton correctly represents all distinct substrings of the string processed up to the current character.; Each state corresponds to an equivalence class of substrings sharing the same end positions.
//   • Tips: Mark terminal states by traversing suffix links from the state representing the full string.; The `last` pointer always tracks the state for the entire string processed.
//   • Pitfalls: Incorrectly handling the three cases for adding a new character can lead to an invalid automaton.; Forgetting to update the `last` state after each character addition breaks incremental construction.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numSub(String s) {
        long MOD = 1_000_000_007;
        long result = 0;
        long count = 0;

        for (char c : s.toCharArray()) {
            if (c == '1') {
                count++;
                result = (result + count) % MOD;
            } else {
                count = 0;
            }
        }

        return (int) result;            
    }
}
