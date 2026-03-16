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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

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
            # Check if there's at least one duplicate character in s
            return len(set(s)) < len(s)
        
        # Find the indices where s and goal differ
        diff = [i for i in range(len(s)) if s[i] != goal[i]]
        
        # There must be exactly 2 differences and they must be swappable
        return len(diff) == 2 and s[diff[0]] == goal[diff[1]] and s[diff[1]] == goal[diff[0]]