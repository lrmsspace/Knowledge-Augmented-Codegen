# Source: https://leetcode.com/problems/number-of-good-ways-to-split-a-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s.
#
# A split is called good if you can split s into two non-empty strings sleft and sright where their concatenation is equal to s (i.e., sleft + sright = s) and the number of distinct letters in sleft and sright is the same.
#
# Return the number of good splits you can make in s.
#
# Example:
# Input: s = "aacaba"
# Output: 2
# Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
# ("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
# ("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
# ("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
# ("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
# ("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def numSplits(self, s):
        """
        :type s: str
        :rtype: int
        """
        left_count = [0] * 26
        right_count = [0] * 26
        
        left_distinct = 0
        right_distinct = 0
        
        for char in s:
            index = ord(char) - ord('a')
            if right_count[index] == 0:
                right_distinct += 1
            right_count[index] += 1
        
        good_splits = 0
        
        for i in range(len(s) - 1):
            index = ord(s[i]) - ord('a')
            left_count[index] += 1
            if left_count[index] == 1:
                left_distinct += 1
            
            right_count[index] -= 1
            if right_count[index] == 0:
                right_distinct -= 1
            
            if left_distinct == right_distinct:
                good_splits += 1
        
        return good_splits