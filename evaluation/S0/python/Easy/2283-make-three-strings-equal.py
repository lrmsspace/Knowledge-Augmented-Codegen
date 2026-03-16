# Source: https://leetcode.com/problems/make-three-strings-equal/   |   Difficulty: Easy
#
# Problem Description:
# You are given three strings: s1, s2, and s3. In one operation you can choose one of these strings and delete its rightmost character. Note that you cannot completely empty a string.
#
# Return the minimum number of operations required to make the strings equal. If it is impossible to make them equal, return -1.
#
# Example:
# Input: s1 = "abc", s2 = "abb", s3 = "ab"
#
# Output: 2
#
# Explanation: Deleting the rightmost character from both s1 and s2 will result in three equal strings.
#
# Constraints:
# 1 <= s1.length, s2.length, s3.length <= 100
# 	s1, s2 and s3 consist only of lowercase English letters.
#

class Solution(object):
    def findMinimumOperations(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: int
        """
        min_length = min(len(s1), len(s2), len(s3))
        common_length = 0
        
        for i in range(1, min_length + 1):
            if s1[-i] == s2[-i] == s3[-i]:
                common_length += 1
            else:
                break
        
        total_operations = (len(s1) - common_length) + (len(s2) - common_length) + (len(s3) - common_length)
        
        if common_length == 0:
            return -1
        
        return total_operations