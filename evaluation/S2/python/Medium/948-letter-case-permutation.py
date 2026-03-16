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
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Generating all K-combinations (bitset, enumeration)
#   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
#   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
#   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
#   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
#   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
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
        def backtrack(path, index):
            if index == len(s):
                res.append(path)
                return
            if s[index].isalpha():
                backtrack(path + s[index].lower(), index + 1)
                backtrack(path + s[index].upper(), index + 1)
            else:
                backtrack(path + s[index], index + 1)

        backtrack("", 0)
        return res