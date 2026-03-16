# Source: https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, find any substring of length 2 which is also present in the reverse of s.
#
# Return true if such a substring exists, and false otherwise.
#
# Example:
# Input: s = "leetcode"
#
# Output: true
#
# Explanation: Substring "ee" is of length 2 which is also present in reverse(s) == "edocteel".
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
# - String Hashing (string, array, hashing)
#   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
#   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
#   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
#   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
#   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isSubstringPresent(self, s):
        """
        :type s: str
        :rtype: bool
        """
        n = len(s)
        if n < 2:
            return False

        # Check for each substring of length 2
        for i in range(n - 1):
            substring = s[i:i+2]
            if substring in s[::-1]:  # Check if it's in the reverse of s
                return True

        return False