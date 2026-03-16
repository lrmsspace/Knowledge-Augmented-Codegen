# Source: https://leetcode.com/problems/mice-and-cheese/   |   Difficulty: Medium
#
# Problem Description:
# There are two mice and n different types of cheese, each type of cheese should be eaten by exactly one mouse.
#
# A point of the cheese with index i (0-indexed) is:
#
#
# 	reward1[i] if the first mouse eats it.
# 	reward2[i] if the second mouse eats it.
#
#
# You are given a positive integer array reward1, a positive integer array reward2, and a non-negative integer k.
#
# Return the maximum points the mice can achieve if the first mouse eats exactly k types of cheese.
#
# Example:
# Input: reward1 = [1,1,3,4], reward2 = [4,4,1,1], k = 2
# Output: 15
# Explanation: In this example, the first mouse eats the 2nd (0-indexed) and the 3rd types of cheese, and the second mouse eats the 0th and the 1st types of cheese.
# The total points are 4 + 4 + 3 + 4 = 15.
# It can be proven that 15 is the maximum total points that the mice can achieve.
#
# Constraints:
# 1 <= n == reward1.length == reward2.length <= 105
# 	1 <= reward1[i], reward2[i] <= 1000
# 	0 <= k <= n
#

class Solution(object):
    def miceAndCheese(self, reward1, reward2, k):
        """
        :type reward1: List[int]
        :type reward2: List[int]
        :type k: int
        :rtype: int
        """
        diffs = [r1 - r2 for r1, r2 in zip(reward1, reward2)]
        indices = sorted(range(len(diffs)), key=lambda i: diffs[i], reverse=True)
        
        total_reward = 0
        
        for i in range(len(reward1)):
            if i < k:
                total_reward += reward1[indices[i]]
            else:
                total_reward += reward2[indices[i]]
        
        return total_reward