# Source: https://leetcode.com/problems/number-of-ways-to-split-a-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary string s, you can split s into 3 non-empty strings s1, s2, and s3 where s1 + s2 + s3 = s.
#
# Return the number of ways s can be split such that the number of ones is the same in s1, s2, and s3. Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: s = "10101"
# Output: 4
# Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
# "1|010|1"
# "1|01|01"
# "10|10|1"
# "10|1|01"
#
# Constraints:
# 3 <= s.length <= 105
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def numWays(self, s):
        """
        :type s: str
        :rtype: int
        """
        MOD = 10**9 + 7
        total_ones = s.count('1')
        
        # If total number of '1's is not divisible by 3, return 0
        if total_ones % 3 != 0:
            return 0
        
        # If there are no '1's, we can split in any two places among the (n-1) gaps
        if total_ones == 0:
            n = len(s)
            return ((n - 1) * (n - 2) // 2) % MOD
        
        ones_per_part = total_ones // 3
        first_cut_ways = 0
        second_cut_ways = 0
        
        count_ones = 0
        
        for char in s:
            if char == '1':
                count_ones += 1
            
            if count_ones == ones_per_part:
                first_cut_ways += 1
            elif count_ones == 2 * ones_per_part:
                second_cut_ways += 1
        
        return (first_cut_ways * second_cut_ways) % MOD