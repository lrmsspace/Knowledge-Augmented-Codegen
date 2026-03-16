# Source: https://leetcode.com/problems/interleaving-string/   |   Difficulty: Medium
#
# Problem Description:
# Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
#
# An interleaving of two strings s and t is a configuration where s and t are divided into n and m substrings respectively, such that:
#
#
# 	s = s1 + s2 + ... + sn
# 	t = t1 + t2 + ... + tm
# 	|n - m| <= 1
# 	The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
#
#
# Note: a + b is the concatenation of strings a and b.
#
# Example:
# Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
# Output: true
# Explanation: One way to obtain s3 is:
# Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
# Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
# Since s3 can be obtained by interleaving s1 and s2, we return true.
#
# Constraints:
# 0 <= s1.length, s2.length <= 100
# 	0 <= s3.length <= 200
# 	s1, s2, and s3 consist of lowercase English letters.
#
#
#  
# Follow up: Could you solve it using only O(s2.length) additional memory space?
#

class Solution(object):
    def isInterleave(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        len1, len2, len3 = len(s1), len(s2), len(s3)
        if len1 + len2 != len3:
            return False
        
        dp = [[False] * (len2 + 1) for _ in range(len1 + 1)]
        dp[0][0] = True
        
        for i in range(len1 + 1):
            for j in range(len2 + 1):
                if i > 0 and s1[i - 1] == s3[i + j - 1]:
                    dp[i][j] = dp[i][j] or dp[i - 1][j]
                if j > 0 and s2[j - 1] == s3[i + j - 1]:
                    dp[i][j] = dp[i][j] or dp[i][j - 1]
        
        return dp[len1][len2]