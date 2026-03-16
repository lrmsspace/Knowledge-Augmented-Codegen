# Source: https://leetcode.com/problems/sum-of-digits-of-string-after-convert/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s consisting of lowercase English letters, and an integer k. Your task is to convert the string into an integer by a special process, and then transform it by summing its digits repeatedly k times. More specifically, perform the following steps:
#
#
# 	Convert s into an integer by replacing each letter with its position in the alphabet (i.e. replace 'a' with 1, 'b' with 2, ..., 'z' with 26).
# 	Transform the integer by replacing it with the sum of its digits.
# 	Repeat the transform operation (step 2) k times in total.
#
#
# For example, if s = "zbax" and k = 2, then the resulting integer would be 8 by the following operations:
#
#
# 	Convert: "zbax" ➝ "(26)(2)(1)(24)" ➝ "262124" ➝ 262124
# 	Transform #1: 262124 ➝ 2 + 6 + 2 + 1 + 2 + 4 ➝ 17
# 	Transform #2: 17 ➝ 1 + 7 ➝ 8
#
#
# Return the resulting integer after performing the operations described above.
#
# Example:
# Input: s = "iiii", k = 1
#
# Output: 36
#
# Explanation:
#
# The operations are as follows:
# - Convert: "iiii" ➝ "(9)(9)(9)(9)" ➝ "9999" ➝ 9999
# - Transform #1: 9999 ➝ 9 + 9 + 9 + 9 ➝ 36
# Thus the resulting integer is 36.
#
# Constraints:
# 1 <= s.length <= 100
# 	1 <= k <= 10
# 	s consists of lowercase English letters.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getLucky(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        # Step 1: Convert string to numbers
        num_str = ""
        for char in s:
            num_str += str(ord(char) - ord('a') + 1)
        
        # Step 2: Transform k times
        current = int(num_str)
        for _ in range(k):
            total = 0
            while current > 0:
                total += current % 10
                current //= 10
            current = total
        
        return current