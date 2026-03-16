// Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer t, representing the number of transformations to perform. In one transformation, every character in s is replaced according to the following rules:
//
//
// 	If the character is 'z', replace it with the string "ab".
// 	Otherwise, replace it with the next character in the alphabet. For example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so on.
//
//
// Return the length of the resulting string after exactly t transformations.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcyy", t = 2
//
// Output: 7
//
// Explanation:
//
//
// 	First Transformation (t = 1):
//
// 	
// 		'a' becomes 'b'
// 		'b' becomes 'c'
// 		'c' becomes 'd'
// 		'y' becomes 'z'
// 		'y' becomes 'z'
// 		String after the first transformation: "bcdzz"
// 	
// 	
// 	Second Transformation (t = 2):
// 	
// 		'b' becomes 'c'
// 		'c' becomes 'd'
// 		'd' becomes 'e'
// 		'z' becomes "ab"
// 		'z' becomes "ab"
// 		String after the second transformation: "cdeabab"
// 	
// 	
// 	Final Length of the string: The string is "cdeabab", which has 7 characters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
// 	1 <= t <= 105
//
// Helpful references (internal KB):
// - Suffix Array (string, array, counting-sort, radix-sort)
//   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
//   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
//   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
//   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
//   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
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

int lengthAfterTransformations(char* s, int t) {
    const int MOD = 1000000007;
    int dp[100001][26];
    
    // Base case: for t = 0, each character contributes 1 to the length
    for (int c = 0; c < 26; ++c) {
        dp[0][c] = 1;
    }
    
    // Fill the dp table for transformations from 1 to t
    for (int time = 1; time <= t; ++time) {
        for (int c = 0; c < 25; ++c) {
            dp[time][c] = dp[time - 1][c + 1]; // 'a' to 'y'
        }
        dp[time][25] = (dp[time - 1][0] + dp[time - 1][1]) % MOD; // 'z' -> "ab"
    }
    
    // Calculate the final length after t transformations
    long long result = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        result = (result + dp[t][s[i] - 'a']) % MOD;
    }
    
    return (int)result;     
}
