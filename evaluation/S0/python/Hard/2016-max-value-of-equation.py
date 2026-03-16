# Source: https://leetcode.com/problems/max-value-of-equation/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array points containing the coordinates of points on a 2D plane, sorted by the x-values, where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You are also given an integer k.
#
# Return the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
#
# It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.
#
# Example:
# Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
# Output: 4
# Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 + |1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1.
# No other pairs satisfy the condition, so we return the max of 4 and 1.
#
# Constraints:
# 2 <= points.length <= 105
# 	points[i].length == 2
# 	-108 <= xi, yi <= 108
# 	0 <= k <= 2 * 108
# 	xi < xj for all 1 <= i < j <= points.length
# 	xi form a strictly increasing sequence.
#

class Solution(object):
    def findMaxValueOfEquation(self, points, k):
        """
        :type points: List[List[int]]
        :type k: int
        :rtype: int
        """
        import collections
        import heapq

        max_value = float('-inf')
        deq = collections.deque()  # will store pairs of (xj, yj - xj)

        for xj, yj in points:
            # Remove points from the front of the deque that are out of the k range
            while deq and xj - deq[0][0] > k:
                deq.popleft()

            # If the deque is not empty, calculate the potential max value
            if deq:
                max_value = max(max_value, yj + xj + deq[0][1])

            # Maintain the deque to keep only the points with the maximum (yj - xj)
            while deq and deq[-1][1] <= yj - xj:
                deq.pop()

            deq.append((xj, yj - xj))

        return max_value