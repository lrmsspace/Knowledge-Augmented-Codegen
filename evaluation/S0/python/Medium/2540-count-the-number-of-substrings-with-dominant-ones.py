# Source: https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string s.
#
# Return the number of substrings with dominant ones.
#
# A string has dominant ones if the number of ones in the string is greater than or equal to the square of the number of zeros in the string.
#
# Example:
# Input: s = "00011"
#
# Output: 5
#
# Explanation:
#
# The substrings with dominant ones are shown in the table below.
#
#
#
# 	
# 		
# 			i
# 			j
# 			s[i..j]
# 			Number of Zeros
# 			Number of Ones
# 		
# 	
# 	
# 		
# 			3
# 			3
# 			1
# 			0
# 			1
# 		
# 		
# 			4
# 			4
# 			1
# 			0
# 			1
# 		
# 		
# 			2
# 			3
# 			01
# 			1
# 			1
# 		
# 		
# 			3
# 			4
# 			11
# 			0
# 			2
# 		
# 		
# 			2
# 			4
# 			011
# 			1
# 			2
#
# Constraints:
# 1 <= s.length <= 4 * 104
# 	s consists only of characters '0' and '1'.
#

class Solution(object):
    def numberOfSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        result = 0
        
        for i in range(n):
            zeros = 0
            ones = 0
            
            for j in range(i, n):
                if s[j] == '0':
                    zeros += 1
                else:
                    ones += 1
                
                if ones >= zeros * zeros:
                    result += 1
        
        return result