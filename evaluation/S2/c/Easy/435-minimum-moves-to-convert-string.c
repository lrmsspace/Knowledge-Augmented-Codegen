// Source: https://leetcode.com/problems/minimum-moves-to-convert-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of n characters which are either 'X' or 'O'.
//
// A move is defined as selecting three consecutive characters of s and converting them to 'O'. Note that if a move is applied to the character 'O', it will stay the same.
//
// Return the minimum number of moves required so that all the characters of s are converted to 'O'.
//
// Example:
// Input: s = "XXX"
// Output: 1
// Explanation: XXX -> OOO
// We select all the 3 characters and convert them in one move.
//
// Constraints:
// 3 <= s.length <= 1000
// 	s[i] is either 'X' or 'O'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Finding repetitions (string, divide-and-conquer, recursion)
//   • When to use: This algorithm is used to find all occurrences of repeating substrings within a given string. It is suitable for problems requiring the identification of periodic patterns or structural redundancies.
//   • Idea: This algorithm, often exemplified by Main-Lorentz, uses a divide-and-conquer strategy with Z-function as a subroutine to efficiently find all repetitions in a string. It typically achieves an O(N log N) time complexity for finding and describing repetitions.
//   • Invariants: All repetitions fully contained within the left or right subproblems are found recursively.; Crossing repetitions are identified by combining information from both subproblems using Z-function.
//   • Tips: Understand the definition of a 'repetition' (e.g., Crochemore triples or (i, p, r) tuples).; Leverage string algorithms like Z-function for efficient substring matching in subproblems.
//   • Pitfalls: Expanding compact repetition tuples to full start/end indices can lead to O(N^2) complexity.; Incorrectly handling string reversal or concatenation for Z-function applications.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumMoves(char* s) {
    int moves = 0;
    for (int i = 0; s[i] != '\0';) {
        if (s[i] == 'X') {
            moves++;
            i += 3; // Skip the next two characters as well
        } else {
            i++;
        }
    }
    return moves;       
}
