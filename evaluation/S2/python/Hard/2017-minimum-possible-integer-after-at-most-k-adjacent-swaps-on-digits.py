# Source: https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string num representing the digits of a very large integer and an integer k. You are allowed to swap any two adjacent digits of the integer at most k times.
#
# Return the minimum integer you can obtain also as a string.
#
# Example:
# Input: num = "4321", k = 4
# Output: "1342"
# Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
#
# Constraints:
# 1 <= num.length <= 3 * 104
# 	num consists of only digits and does not contain leading zeros.
# 	1 <= k <= 109
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
    def minInteger(self, num, k):
        """
        :type num: str
        :type k: int
        :rtype: str
        """
        from collections import defaultdict
        import bisect
        
        # Step 1: Store the indices of each digit
        digit_indices = defaultdict(list)
        for i, digit in enumerate(num):
            digit_indices[digit].append(i)
        
        result = []
        current_pos = 0
        
        while k > 0 and current_pos < len(num):
            found = False
            for digit in map(str, range(10)):
                if digit in digit_indices and digit_indices[digit]:
                    index = digit_indices[digit][0]
                    if index - current_pos <= k:
                        # We can swap this digit to the current position
                        result.append(digit)
                        k -= (index - current_pos)
                        current_pos += 1
                        # Remove the used index
                        digit_indices[digit].pop(0)
                        found = True
                        break
            
            if not found:
                break
        
        # Append remaining digits in order
        for digit in map(str, range(10)):
            if digit in digit_indices:
                for index in digit_indices[digit]:
                    if index >= current_pos:
                        result.append(digit)
        
        return ''.join(result)