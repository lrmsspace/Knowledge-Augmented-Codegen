// Source: https://leetcode.com/problems/shifting-letters/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of lowercase English letters and an integer array shifts of the same length.
//
// Call the shift() of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a').
//
//
// 	For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.
//
//
// Now for each shifts[i] = x, we want to shift the first i + 1 letters of s, x times.
//
// Return the final string after all such shifts to s are applied.
//
// Example:
// Input: s = "abc", shifts = [3,5,9]
// Output: "rpl"
// Explanation: We start with "abc".
// After shifting the first 1 letters of s by 3, we have "dbc".
// After shifting the first 2 letters of s by 5, we have "igc".
// After shifting the first 3 letters of s by 9, we have "rpl", the answer.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	shifts.length == s.length
// 	0 <= shifts[i] <= 109
//
// Helpful references (internal KB):
// - Suffix Array (string, array, counting-sort, radix-sort)
//   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
//   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
//   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
//   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
//   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        int n = s.size();
        vector<long long> prefixShifts(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixShifts[i + 1] = (prefixShifts[i] + shifts[i]) % 26;
        }

        string result = s;
        for (int i = 0; i < n; ++i) {
            int totalShift = prefixShifts[n] - prefixShifts[i];
            totalShift = (totalShift % 26 + 26) % 26; // Ensure non-negative
            result[i] = 'a' + (s[i] - 'a' + totalShift) % 26;
        }

        return result;          
    }
};
