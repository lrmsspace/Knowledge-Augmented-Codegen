# Source: https://leetcode.com/problems/total-characters-in-string-after-transformations-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and an integer t, representing the number of transformations to perform. In one transformation, every character in s is replaced according to the following rules:
#
#
# 	If the character is 'z', replace it with the string "ab".
# 	Otherwise, replace it with the next character in the alphabet. For example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so on.
#
#
# Return the length of the resulting string after exactly t transformations.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: s = "abcyy", t = 2
#
# Output: 7
#
# Explanation:
#
#
# 	First Transformation (t = 1):
#
# 	
# 		'a' becomes 'b'
# 		'b' becomes 'c'
# 		'c' becomes 'd'
# 		'y' becomes 'z'
# 		'y' becomes 'z'
# 		String after the first transformation: "bcdzz"
# 	
# 	
# 	Second Transformation (t = 2):
# 	
# 		'b' becomes 'c'
# 		'c' becomes 'd'
# 		'd' becomes 'e'
# 		'z' becomes "ab"
# 		'z' becomes "ab"
# 		String after the second transformation: "cdeabab"
# 	
# 	
# 	Final Length of the string: The string is "cdeabab", which has 7 characters.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists only of lowercase English letters.
# 	1 <= t <= 105
#

class Solution(object):
    def lengthAfterTransformations(self, s, t):
        """
        :type s: str
        :type t: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # Precompute the lengths after transformations for each character
        dp = [[0] * (t + 1) for _ in range(26)]
        
        for i in range(26):
            dp[i][0] = 1  # Base case: length is 1 with 0 transformations
        
        for