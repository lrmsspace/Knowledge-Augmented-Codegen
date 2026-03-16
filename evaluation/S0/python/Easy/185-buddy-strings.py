# Source: https://leetcode.com/problems/buddy-strings/   |   Difficulty: Easy
#
# Problem Description:
# Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.
#
# Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].
#
#
# 	For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
#
# Example:
# Input: s = "ab", goal = "ba"
# Output: true
# Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
#
# Constraints:
# 1 <= s.length, goal.length <= 2 * 104
# 	s and goal consist of lowercase letters.
#

class Solution(object):
    def buddyStrings(self, s, goal):
        """
        :type s: str
        :type goal: str
        :rtype: bool
        """
        if len(s) != len(goal):
            return False
        
        if s == goal:
            seen = set()
            for char in s:
                if char in seen:
                    return True
                seen.add(char)
            return False
        
        diff = []
        for i in range(len(s)):
            if s[i] != goal[i]:
                diff.append(i)
                if len(diff) > 2:
                    return False
        
        if len(diff) != 2:
            return False
        
        i, j = diff
        return s[i] == goal[j] and s[j] == goal[i]