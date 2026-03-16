# Source: https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/   |   Difficulty: Hard
#
# Problem Description:
# There are n people and 40 types of hats labeled from 1 to 40.
#
# Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.
#
# Return the number of ways that n people can wear different hats from each other.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: hats = [[3,4],[4,5],[5]]
# Output: 1
# Explanation: There is only one way to choose hats given the conditions. 
# First person choose hat 3, Second person choose hat 4 and last one hat 5.
#
# Constraints:
# n == hats.length
# 	1 <= n <= 10
# 	1 <= hats[i].length <= 40
# 	1 <= hats[i][j] <= 40
# 	hats[i] contains a list of unique integers.
#

class Solution(object):
    def numberWays(self, hats):
        """
        :type hats: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(hats)
        hat_to_people = [[] for _ in range(41)]
        
        for person, hat_list in enumerate(hats):
            for hat in hat_list:
                hat_to_people[hat].append(person)
        
        dp = [0] * (1 << n)
        dp[0] = 1
        
        for hat in range(1, 41):
            new_dp = dp[:]
            for mask in range(1 << n):
                if dp[mask] == 0:
                    continue
                for person in hat_to_people[hat]:
                    if mask & (1 << person) == 0:
                        new_mask = mask | (1 << person)
                        new_dp[new_mask] = (new_dp[new_mask] + dp[mask]) % MOD
            dp = new_dp
        
        return dp[(1 << n) - 1]