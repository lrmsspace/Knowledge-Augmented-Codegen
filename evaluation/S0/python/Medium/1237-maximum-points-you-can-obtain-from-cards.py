# Source: https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/   |   Difficulty: Medium
#
# Problem Description:
# There are several cards arranged in a row, and each card has an associated number of points. The points are given in the integer array cardPoints.
#
# In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.
#
# Your score is the sum of the points of the cards you have taken.
#
# Given the integer array cardPoints and the integer k, return the maximum score you can obtain.
#
# Example:
# Input: cardPoints = [1,2,3,4,5,6,1], k = 3
# Output: 12
# Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
#
# Constraints:
# 1 <= cardPoints.length <= 105
# 	1 <= cardPoints[i] <= 104
# 	1 <= k <= cardPoints.length
#

class Solution(object):
    def maxScore(self, cardPoints, k):
        """
        :type cardPoints: List[int]
        :type k: int
        :rtype: int
        """
        n = len(cardPoints)
        total_points = sum(cardPoints)
        
        if k == n:
            return total_points
        
        window_size = n - k
        current_window_sum = sum(cardPoints[:window_size])
        min_window_sum = current_window_sum
        
        for i in range(window_size, n):
            current_window_sum += cardPoints[i] - cardPoints[i - window_size]
            min_window_sum = min(min_window_sum, current_window_sum)
        
        return total_points - min_window_sum