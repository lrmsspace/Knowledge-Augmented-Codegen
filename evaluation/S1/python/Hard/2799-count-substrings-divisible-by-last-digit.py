# Source: https://leetcode.com/problems/count-substrings-divisible-by-last-digit/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s consisting of digits.
#
# Return the number of substrings of s divisible by their non-zero last digit.
#
# Note: A substring may contain leading zeros.
#
# Example:
# Input: s = "12936"
#
# Output: 11
#
# Explanation:
#
# Substrings "29", "129", "293" and "2936" are not divisible by their last digit. There are 15 substrings in total, so the answer is 15 - 4 = 11.
#
# Constraints:
# 1 <= s.length <= 105
#  s consists of digits only.
#
# Helpful references (internal KB):
# - Suffix array (array, string, suffix-array, divide-and-conquer, recursion)
#   • When to use: Use when you need to efficiently perform various string operations like pattern searching, finding repeated substrings, or comparing suffixes lexicographically on a given text. It is a fundamental data structure for advanced string algorithms.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string. It allows for efficient string operations, with construction typically achievable in O(N log N) or O(N) time for advanced algorithms.
#   • Invariants: The suffix array SA[i] stores the starting index of the i-th lexicographically smallest suffix.; All suffixes of the input string are present exactly once in the suffix array.
#   • Tips: Consider using SA-IS for optimal O(N) construction time and space complexity.; Pair the suffix array with an LCP array for enhanced functionality, such as finding longest common substrings.
#   • Pitfalls: Naive O(N^2 log N) construction is too slow for large input strings.; Implementing linear-time algorithms like SA-IS or DC3 can be complex and error-prone.
# - palindrome-partitioning (string, array, backtracking, recursion)
#   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
#   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
#   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
#   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
#   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        count = 0
        n = len(s)

        for i in range(n):
            last_digit = int(s[i])
            if last_digit == 0:
                continue

            for j in range(i + 1):
                substring = s[j:i + 1]
                if int(substring) % last_digit == 0:
                    count += 1

        return count