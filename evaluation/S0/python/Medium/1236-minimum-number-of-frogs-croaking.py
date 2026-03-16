# Source: https://leetcode.com/problems/minimum-number-of-frogs-croaking/   |   Difficulty: Medium
#
# Problem Description:
# You are given the string croakOfFrogs, which represents a combination of the string "croak" from different frogs, that is, multiple frogs can croak at the same time, so multiple "croak" are mixed.
#
# Return the minimum number of different frogs to finish all the croaks in the given string.
#
# A valid "croak" means a frog is printing five letters 'c', 'r', 'o', 'a', and 'k' sequentially. The frogs have to print all five letters to finish a croak. If the given string is not a combination of a valid "croak" return -1.
#
# Example:
# Input: croakOfFrogs = "croakcroak"
# Output: 1 
# Explanation: One frog yelling "croak" twice.
#
# Constraints:
# 1 <= croakOfFrogs.length <= 105
# 	croakOfFrogs is either 'c', 'r', 'o', 'a', or 'k'.
#

class Solution(object):
    def minNumberOfFrogs(self, croakOfFrogs):
        """
        :type croakOfFrogs: str
        :rtype: int
        """
        count = [0] * 5  # c, r, o, a, k
        frogs = 0
        max_frogs = 0
        
        for char in croakOfFrogs:
            if char == 'c':
                count[0] += 1
                frogs += 1
                max_frogs = max(max_frogs, frogs)
            elif char == 'r':
                count[1] += 1
                if count[1] > count[0]:
                    return -1
            elif char == 'o':
                count[2] += 1
                if count[2] > count[1]:
                    return -1
            elif char == 'a':
                count[3] += 1
                if count[3] > count[2]:
                    return -1
            elif char == 'k':
                count[4] += 1
                if count[4] > count[3]:
                    return -1
                frogs -= 1
        
        if count[0] == count[1] == count[2] == count[3] == count[4]:
            return max_frogs
        else:
            return -1