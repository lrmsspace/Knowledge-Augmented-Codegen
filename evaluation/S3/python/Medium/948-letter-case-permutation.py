# Source: https://leetcode.com/problems/letter-case-permutation/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.
#
# Return a list of all possible strings we could create. Return the output in any order.
#
# Example:
# Input: s = "a1b2"
# Output: ["a1b2","a1B2","A1b2","A1B2"]
#
# Constraints:
# 1 <= s.length <= 12
# 	s consists of lowercase English letters, uppercase English letters, and digits.
#
# Helpful references (internal KB):
# - palindrome-partitioning (string, array, backtracking, recursion)
#   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
#   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
#   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
#   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
#   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
# - Generating all K-combinations (bitset, recursion, enumeration)
#   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
#   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
#   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
#   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
#   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def letterCasePermutation(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        res = []
        def backtrack(start, path):
            if start == len(s):
                res.append(path)
                return
            if s[start].isalpha():
                backtrack(start + 1, path + s[start].lower())
                backtrack(start + 1, path + s[start].upper())
            else:
                backtrack(start + 1, path + s[start])
        
        backtrack(0, "")
        return res