# Source: https://leetcode.com/problems/find-the-substring-with-maximum-cost/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s, a string chars of distinct characters and an integer array vals of the same length as chars.
#
# The cost of the substring is the sum of the values of each character in the substring. The cost of an empty string is considered 0.
#
# The value of the character is defined in the following way:
#
#
# 	If the character is not in the string chars, then its value is its corresponding position (1-indexed) in the alphabet.
#
# 	
# 		For example, the value of 'a' is 1, the value of 'b' is 2, and so on. The value of 'z' is 26.
# 	
# 	
# 	Otherwise, assuming i is the index where the character occurs in the string chars, then its value is vals[i].
#
#
# Return the maximum cost among all substrings of the string s.
#
# Example:
# Input: s = "adaa", chars = "d", vals = [-1000]
# Output: 2
# Explanation: The value of the characters "a" and "d" is 1 and -1000 respectively.
# The substring with the maximum cost is "aa" and its cost is 1 + 1 = 2.
# It can be proven that 2 is the maximum cost.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consist of lowercase English letters.
# 	1 <= chars.length <= 26
# 	chars consist of distinct lowercase English letters.
# 	vals.length == chars.length
# 	-1000 <= vals[i] <= 1000
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumCostSubstring(self, s, chars, vals):
        """
        :type s: str
        :type chars: str
        :type vals: List[int]
        :rtype: int
        """
        char_value = {chr(i + ord('a')): i + 1 for i in range(26)}
        for i, c in enumerate(chars):
            char_value[c] = vals[i]

        max_cost = 0
        current_cost = 0

        for ch in s:
            current_cost += char_value[ch]
            if current_cost < 0:
                current_cost = 0
            max_cost = max(max_cost, current_cost)

        return max_cost