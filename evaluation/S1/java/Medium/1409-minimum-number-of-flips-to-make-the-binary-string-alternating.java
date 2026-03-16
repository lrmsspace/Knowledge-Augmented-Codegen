// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:
//
//
// 	Type-1: Remove the character at the start of the string s and append it to the end of the string.
// 	Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
//
//
// Return the minimum number of type-2 operations you need to perform such that s becomes alternating.
//
// The string is called alternating if no two adjacent characters are equal.
//
//
// 	For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
//
// Example:
// Input: s = "111000"
// Output: 2
// Explanation: Use the first operation two times to make s = "100011".
// Then, use the second operation on the third and sixth elements to make s = "101010".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minFlips(String s) {
        int n = s.length();
        StringBuilder sb = new StringBuilder(s);
        sb.append(s);
        String doubledS = sb.toString();

        // Generate the two possible alternating patterns
        StringBuilder pattern1 = new StringBuilder();
        StringBuilder pattern2 = new StringBuilder();
        for (int i = 0; i < doubledS.length(); i++) {
            if (i % 2 == 0) {
                pattern1.append('0');
                pattern2.append('1');
            } else {
                pattern1.append('1');
                pattern2.append('0');
            }
        }

        int minFlips = Integer.MAX_VALUE;
        int count1 = 0; // Mismatches with pattern1
        int count2 = 0; // Mismatches with pattern2

        for (int i = 0; i < doubledS.length(); i++) {
            if (doubledS.charAt(i) != pattern1.charAt(i)) {
                count1++;
            }
            if (doubledS.charAt(i) != pattern2.charAt(i)) {
                count2++;
            }

            // When the window exceeds size n, remove the leftmost character
            if (i >= n) {
                if (doubledS.charAt(i - n) != pattern1.charAt(i - n)) {
                    count1--;
                }
                if (doubledS.charAt(i - n) != pattern2.charAt(i - n)) {
                    count2--;
                }
            }

            // Once we have a valid window of size n, update the minimum flips
            if (i >= n - 1) {
                minFlips = Math.min(minFlips, Math.min(count1, count2));
            }
        }

        return minFlips;            
    }
}
