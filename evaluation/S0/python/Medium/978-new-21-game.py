# Source: https://leetcode.com/problems/new-21-game/   |   Difficulty: Medium
#
# Problem Description:
# Alice plays the following game, loosely based on the card game "21".
#
# Alice starts with 0 points and draws numbers while she has less than k points. During each draw, she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an integer. Each draw is independent and the outcomes have equal probabilities.
#
# Alice stops drawing numbers when she gets k or more points.
#
# Return the probability that Alice has n or fewer points.
#
# Answers within 10-5 of the actual answer are considered accepted.
#
# Example:
# Input: n = 10, k = 1, maxPts = 10
# Output: 1.00000
# Explanation: Alice gets a single card, then stops.
#
# Constraints:
# 0 <= k <= n <= 104
# 	1 <= maxPts <= 104
#

class Solution(object):
    def new21Game(self, n, k, maxPts):
        """
        :type n: int
        :type k: int
        :type maxPts: int
        :rtype: float
        """
        if k == 0 or n >= k + maxPts:
            return 1.0
        
        dp = [0.0] * (n + 1)
        dp[0] = 1.0
        window_sum = 1.0
        result = 0.0
        
        for i in range(1, n + 1):
            dp[i] = window_sum / maxPts
            
            if i < k:
                window_sum += dp[i]
            else:
                result += dp[i]
            
            if i - maxPts >= 0:
                window_sum -= dp[i - maxPts]
        
        return result