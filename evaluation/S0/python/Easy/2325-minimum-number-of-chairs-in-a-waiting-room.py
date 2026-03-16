# Source: https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s. Simulate events at each second i:
#
#
# 	If s[i] == 'E', a person enters the waiting room and takes one of the chairs in it.
# 	If s[i] == 'L', a person leaves the waiting room, freeing up a chair.
#
#
# Return the minimum number of chairs needed so that a chair is available for every person who enters the waiting room given that it is initially empty.
#
# Example:
# Input: s = "EEEEEEE"
#
# Output: 7
#
# Explanation:
#
# After each second, a person enters the waiting room and no person leaves it. Therefore, a minimum of 7 chairs is needed.
#
# Constraints:
# 1 <= s.length <= 50
# 	s consists only of the letters 'E' and 'L'.
# 	s represents a valid sequence of entries and exits.
#

class Solution(object):
    def minimumChairs(self, s):
        """
        :type s: str
        :rtype: int
        """
        current_chairs = 0
        max_chairs = 0
        
        for event in s:
            if event == 'E':
                current_chairs += 1
                max_chairs = max(max_chairs, current_chairs)
            elif event == 'L':
                current_chairs -= 1
        
        return max_chairs