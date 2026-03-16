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
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var minimumBeautifulSubstrings = function(s) {
    const n = s.length;
    const powersOf5 = new Set();

    // Precompute powers of 5 up to 2^15 (since the maximum length of s is 15)
    for (let i = 0; i < 15; i++) {
        powersOf5.add((1 << i) - 1); // 2^i - 1 gives us the binary representation of a power of 5
    }

    const dp = Array(n + 1).fill(Infinity);
    dp[0] = 0; // Base case: 0 substrings needed for an empty string

    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < i; j++) {
            if (s[j] === '0') continue; // Skip substrings with leading zeros
            const num = parseInt(s.substring(j, i), 2); // Convert binary substring to integer
            if (powersOf5.has(num)) {
                dp[i] = Math.min(dp[i], dp[j] + 1);
            }
        }
    }

    return dp[n] === Infinity ? -1 : dp[n];
};
