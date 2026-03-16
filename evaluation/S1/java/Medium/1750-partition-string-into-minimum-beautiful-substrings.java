// Source: https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, partition the string into one or more substrings such that each substring is beautiful.
//
// A string is beautiful if:
//
//
// 	It doesn't contain leading zeros.
// 	It's the binary representation of a number that is a power of 5.
//
//
// Return the minimum number of substrings in such partition. If it is impossible to partition the string s into beautiful substrings, return -1.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "1011"
// Output: 2
// Explanation: We can paritition the given string into ["101", "1"].
// - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
// - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
// It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.
//
// Constraints:
// 1 <= s.length <= 15
// 	s[i] is either '0' or '1'.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isPowerOfFive(String s) {
        if (s.charAt(0) == '0') {
            return false;
        }
        long num = 0;
        for (char c : s.toCharArray()) {
            num = (num << 1) + (c - '0');
        }
        while (num > 1) {
            if (num % 5 != 0) {
                return false;
            }
            num /= 5;
        }
        return num == 1;
    }
    public int minimumBeautifulSubstrings(String s) {
        int n = s.length();
        int[] dp = new int[n + 1];
        final int INF = Integer.MAX_VALUE / 2;
        for (int i = 0; i <= n; i++) {
            dp[i] = INF;
        }
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                String sub = s.substring(j, i);
                if (isPowerOfFive(sub)) {
                    dp[i] = Math.min(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n] == INF ? -1 : dp[n];           
    }
}
