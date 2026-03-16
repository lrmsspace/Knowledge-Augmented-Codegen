# Source: https://leetcode.com/problems/distribute-candies-among-children-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given two positive integers n and limit.
#
# Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
#
# Example:
# Input: n = 5, limit = 2
# Output: 3
# Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
#
# Constraints:
# 1 <= n <= 50
# 	1 <= limit <= 50
#

class Solution(object):
    def distributeCandies(self, n, limit):
        """
        :type n: int
        :type limit: int
        :rtype: int
        """
        count = 0
        for i in range(min(limit, n) + 1):
            for j in range(min(limit, n - i) + 1):
                k = n - i - j
                if 0 <= k <= limit:
                    count += 1
        return count