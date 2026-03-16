// Source: https://leetcode.com/problems/find-the-substring-with-maximum-cost/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, a string chars of distinct characters and an integer array vals of the same length as chars.
//
// The cost of the substring is the sum of the values of each character in the substring. The cost of an empty string is considered 0.
//
// The value of the character is defined in the following way:
//
//
// 	If the character is not in the string chars, then its value is its corresponding position (1-indexed) in the alphabet.
//
// 	
// 		For example, the value of 'a' is 1, the value of 'b' is 2, and so on. The value of 'z' is 26.
// 	
// 	
// 	Otherwise, assuming i is the index where the character occurs in the string chars, then its value is vals[i].
//
//
// Return the maximum cost among all substrings of the string s.
//
// Example:
// Input: s = "adaa", chars = "d", vals = [-1000]
// Output: 2
// Explanation: The value of the characters "a" and "d" is 1 and -1000 respectively.
// The substring with the maximum cost is "aa" and its cost is 1 + 1 = 2.
// It can be proven that 2 is the maximum cost.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consist of lowercase English letters.
// 	1 <= chars.length <= 26
// 	chars consist of distinct lowercase English letters.
// 	vals.length == chars.length
// 	-1000 <= vals[i] <= 1000
//
// Helpful references (internal KB):
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximumCostSubstring(String s, String chars, int[] vals) {
        // Step 1: Create a mapping of characters to their corresponding values.
        Map<Character, Integer> charValueMap = new HashMap<>();
        for (int i = 0; i < chars.length(); i++) {
            charValueMap.put(chars.charAt(i), vals[i]);
        }

        // Step 2: Calculate the cost of each character in the string s.
        int[] costArray = new int[s.length()];
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            costArray[i] = charValueMap.getOrDefault(c, c - 'a' + 1);
        }

        // Step 3: Use Kadane's algorithm to find the maximum cost substring.
        int maxCost = Integer.MIN_VALUE;
        int currentCost = 0;

        for (int cost : costArray) {
            currentCost += cost;
            maxCost = Math.max(maxCost, currentCost);
            if (currentCost < 0) {
                currentCost = 0; // Reset if the current cost becomes negative
            }
        }

        return maxCost;         
    }
}
