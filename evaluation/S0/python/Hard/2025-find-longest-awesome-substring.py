# Source: https://leetcode.com/problems/find-longest-awesome-substring/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it a palindrome.
#
# Return the length of the maximum length awesome substring of s.
#
# Example:
# Input: s = "3242415"
# Output: 5
# Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists only of digits.
#

class Solution(object):
    def longestAwesome(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        prefix = 0
        pos = {0: -1}
        res = 1
        
        for i in range(n):
            digit = int(s[i])
            prefix ^= (1 << digit)
            
            if prefix in pos:
                res = max(res, i - pos[prefix])
            else:
                pos[prefix] = i
            
            for j in range(10):
                mask = prefix ^ (1 << j)
                if mask in pos:
                    res = max(res, i - pos[mask])
        
        return res