# Source: https://leetcode.com/problems/shortest-impossible-sequence-of-rolls/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array rolls of length n and an integer k. You roll a k sided dice numbered from 1 to k, n times, where the result of the ith roll is rolls[i].
#
# Return the length of the shortest sequence of rolls so that there's no such subsequence in rolls.
#
# A sequence of rolls of length len is the result of rolling a k sided dice len times.
#
# Example:
# Input: rolls = [4,2,1,2,3,3,2,4,1], k = 4
# Output: 3
# Explanation: Every sequence of rolls of length 1, [1], [2], [3], [4], can be taken from rolls.
# Every sequence of rolls of length 2, [1, 1], [1, 2], ..., [4, 4], can be taken from rolls.
# The sequence [1, 4, 2] cannot be taken from rolls, so we return 3.
# Note that there are other sequences that cannot be taken from rolls.
#
# Constraints:
# n == rolls.length
# 	1 <= n <= 105
# 	1 <= rolls[i] <= k <= 105
#

class Solution(object):
    def shortestSequence(self, rolls, k):
        """
        :type rolls: List[int]
        :type k: int
        :rtype: int
        """
        seen = set()
        result = 1
        
        for roll in rolls:
            seen.add(roll)
            if len(seen) == k:
                result += 1
                seen.clear()
        
        return result