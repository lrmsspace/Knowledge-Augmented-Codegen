// Source: https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s.
//
// Return the number of substrings with dominant ones.
//
// A string has dominant ones if the number of ones in the string is greater than or equal to the square of the number of zeros in the string.
//
// Example:
// Input: s = "00011"
//
// Output: 5
//
// Explanation:
//
// The substrings with dominant ones are shown in the table below.
//
//
//
// 	
// 		
// 			i
// 			j
// 			s[i..j]
// 			Number of Zeros
// 			Number of Ones
// 		
// 	
// 	
// 		
// 			3
// 			3
// 			1
// 			0
// 			1
// 		
// 		
// 			4
// 			4
// 			1
// 			0
// 			1
// 		
// 		
// 			2
// 			3
// 			01
// 			1
// 			1
// 		
// 		
// 			3
// 			4
// 			11
// 			0
// 			2
// 		
// 		
// 			2
// 			4
// 			011
// 			1
// 			2
//
// Constraints:
// 1 <= s.length <= 4 * 104
// 	s consists only of characters '0' and '1'.
//
// Helpful references (internal KB):
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numberOfSubstrings(String s) {
        int n = s.length();
        int maxZeros = (int) Math.sqrt(n) + 2;
        int[][] prefixCount = new int[n + 1][maxZeros];
        int zeros = 0, ones = 0;

        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == '0') {
                zeros++;
            } else {
                ones++;
            }

            for (int j = 0; j < maxZeros; j++) {
                prefixCount[i + 1][j] = prefixCount[i][j];
            }

            if (zeros < maxZeros) {
                prefixCount[i + 1][zeros]++;
            }
        }

        int result = 0;

        for (int i = 0; i < n; i++) {
            zeros = 0;
            ones = 0;

            for (int j = i; j < n; j++) {
                if (s.charAt(j) == '0') {
                    zeros++;
                } else {
                    ones++;
                }

                if (zeros >= maxZeros) {
                    break;
                }

                if (ones >= zeros * zeros) {
                    result++;
                }
            }
        }

        return result;          
    }
}
