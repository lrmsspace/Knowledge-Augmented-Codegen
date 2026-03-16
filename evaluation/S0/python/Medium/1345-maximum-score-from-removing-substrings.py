# Source: https://leetcode.com/problems/maximum-score-from-removing-substrings/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and two integers x and y. You can perform two types of operations any number of times.
#
#
# 	Remove substring "ab" and gain x points.
#
# 	
# 		For example, when removing "ab" from "cabxbae" it becomes "cxbae".
# 	
# 	
# 	Remove substring "ba" and gain y points.
# 	
# 		For example, when removing "ba" from "cabxbae" it becomes "cabxe".
# 	
# 	
#
#
# Return the maximum points you can gain after applying the above operations on s.
#
# Example:
# Input: s = "cdbcbbaaabab", x = 4, y = 5
# Output: 19
# Explanation:
# - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
# - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
# - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
# - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
# Total score = 5 + 4 + 5 + 5 = 19.
#
# Constraints:
# 1 <= s.length <= 105
# 	1 <= x, y <= 104
# 	s consists of lowercase English letters.
#

class Solution(object):
    def maximumGain(self, s, x, y):
        """
        :type s: str
        :type x: int
        :type y: int
        :rtype: int
        """
        stack = []
        total_score = 0
        
        # Determine the order of removal based on points
        first_pair = ('a', 'b', x) if x >= y else ('b', 'a', y)
        second_pair = ('b', 'a', y) if x >= y else ('a', 'b', x)
        
        # First pass: remove the higher scoring pair
        for char in s:
            if stack and stack[-1] == first_pair[0] and char == first_pair[1]:
                stack.pop()
                total_score += first_pair[2]
            else:
                stack.append(char)
        
        # Prepare for second pass
        s2 = ''.join(stack)
        stack = []
        
        # Second pass: remove the lower scoring pair
        for char in s2:
            if stack and stack[-1] == second_pair[0] and char == second_pair[1]:
                stack.pop()
                total_score += second_pair[2]
            else:
                stack.append(char)
        
        return total_score