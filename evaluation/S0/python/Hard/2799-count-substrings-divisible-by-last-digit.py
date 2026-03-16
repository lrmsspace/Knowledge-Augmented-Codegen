# Source: https://leetcode.com/problems/count-substrings-divisible-by-last-digit/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s consisting of digits.
#
# Return the number of substrings of s divisible by their non-zero last digit.
#
# Note: A substring may contain leading zeros.
#
# Example:
# Input: s = "12936"
#
# Output: 11
#
# Explanation:
#
# Substrings "29", "129", "293" and "2936" are not divisible by their last digit. There are 15 substrings in total, so the answer is 15 - 4 = 11.
#
# Constraints:
# 1 <= s.length <= 105
#  s consists of digits only.
#

class Solution(object):
    def countSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        count = 0
        
        for i in range(n):
            last_digit = int(s[i])
            if last_digit == 0:
                continue
            
            for j in range(i, n):
                substring = s[i:j+1]
                num = int(substring)
                
                if num % last_digit == 0:
                    count += 1
                    
        return count