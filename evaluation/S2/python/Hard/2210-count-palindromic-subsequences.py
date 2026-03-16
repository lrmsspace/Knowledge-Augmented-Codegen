# Source: https://leetcode.com/problems/count-palindromic-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.
#
# Note:
#
#
# 	A string is palindromic if it reads the same forward and backward.
# 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
#
# Example:
# Input: s = "103301"
# Output: 2
# Explanation: 
# There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301". 
# Two of them (both equal to "10301") are palindromic.
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of digits.
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - String Hashing (string, number, hashing, prefix-sum)
#   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
#   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
#   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
#   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
#   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPalindromes(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)
        
        # Count of palindromic subsequences of length 5
        count = 0
        
        # Precompute prefix and suffix counts for each digit
        prefix_count = [[0] * 10 for _ in range(n)]
        suffix_count = [[0] * 10 for _ in range(n)]
        
        # Fill prefix counts
        for i in range(n):
            digit = int(s[i])
            if i > 0:
                for d in range(10):
                    prefix_count[i][d] = prefix_count[i-1][d]
            prefix_count[i][digit] += 1
        
        # Fill suffix counts
        for i in range(n-1, -1, -1):
            digit = int(s[i])
            if i < n-1:
                for d in range(10):
                    suffix_count[i][d] = suffix_count[i+1][d]
            suffix_count[i][digit] += 1
        
        # Count palindromic subsequences of the form "a b c b a"
        for j in range(2, n-2):
            middle_digit = int(s[j])
            for a in range(10):
                for b in range(10):
                    count += (prefix_count[j-1][a] * prefix_count[j-1][b]) * (suffix_count[j+1][b] * suffix_count[j+1][a])
                    count %= MOD
        
        return count