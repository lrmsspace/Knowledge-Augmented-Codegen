# Source: https://leetcode.com/problems/reordered-power-of-2/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n. We reorder the digits in any order (including the original order) such that the leading digit is not zero.
#
# Return true if and only if we can do this so that the resulting number is a power of two.
#
# Example:
# Input: n = 1
# Output: true
#
# Constraints:
# 1 <= n <= 109
#

class Solution(object):
    def reorderedPowerOf2(self, n):
        """
        :type n: int
        :rtype: bool
        """
        from collections import Counter
        
        def digit_count(x):
            return Counter(str(x))
        
        target_count = digit_count(n)
        
        for i in range(31):  # 2^30 is the largest power of 2 less than 10^9
            if digit_count(1 << i) == target_count:
                return True
        
        return False