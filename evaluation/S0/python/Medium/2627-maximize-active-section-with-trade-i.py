# Source: https://leetcode.com/problems/maximize-active-section-with-trade-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string s of length n, where:
#
#
# 	'1' represents an active section.
# 	'0' represents an inactive section.
#
#
# You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
#
#
# 	Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
# 	Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
#
#
# Return the maximum number of active sections in s after making the optimal trade.
#
# Note: Treat s as if it is augmented with a '1' at both ends, forming t = '1' + s + '1'. The augmented '1's do not contribute to the final count.
#
# Example:
# Input: s = "01"
#
# Output: 1
#
# Explanation:
#
# Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
#
# Constraints:
# 1 <= n == s.length <= 105
# 	s[i] is either '0' or '1'
#

class Solution(object):
    def maxActiveSectionsAfterTrade(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        total_ones = s.count('1')
        
        # Edge case: If there are no '0's or no '1's, return total_ones
        if total_ones == 0 or total_ones == n:
            return total_ones
        
        max_gain = 0
        
        i = 0
        while i < n:
            if s[i] == '1':
                i += 1
                continue
            
            # Found a block of '0's
            start = i
            while i < n and s[i] == '0':
                i += 1
            end = i
            
            zeros_count = end - start
            
            # Count surrounding '1's
            left_ones = 0
            right_ones = 0
            
            if start > 0 and s[start - 1] == '1':
                j = start - 1
                while j >= 0 and s[j] == '1':
                    left_ones += 1
                    j -= 1
            
            if end < n and s[end] == '1':
                j = end
                while j < n and s[j] == '1':
                    right_ones += 1
                    j += 1
            
            # Calculate gain from this trade
            gain = zeros_count + min(left_ones, right_ones)
            max_gain = max(max_gain, gain)
        
        return total_ones + max_gain