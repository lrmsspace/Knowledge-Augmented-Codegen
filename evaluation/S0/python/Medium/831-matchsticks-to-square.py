# Source: https://leetcode.com/problems/matchsticks-to-square/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
#
# Return true if you can make this square and false otherwise.
#
# Example:
# Input: matchsticks = [1,1,2,2,2]
# Output: true
# Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
#
# Constraints:
# 1 <= matchsticks.length <= 15
# 	1 <= matchsticks[i] <= 108
#

class Solution(object):
    def makesquare(self, matchsticks):
        """
        :type matchsticks: List[int]
        :rtype: bool
        """
        total_length = sum(matchsticks)
        if total_length % 4 != 0:
            return False
        
        side_length = total_length // 4
        matchsticks.sort(reverse=True)
        
        sides = [0] * 4
        
        def backtrack(index):
            if index == len(matchsticks):
                return all(side == side_length for side in sides)
            
            for i in range(4):
                if sides[i] + matchsticks[index] <= side_length:
                    sides[i] += matchsticks[index]
                    if backtrack(index + 1):
                        return True
                    sides[i] -= matchsticks[index]
                
                if sides[i] == 0:
                    break
            
            return False
        
        return backtrack(0)