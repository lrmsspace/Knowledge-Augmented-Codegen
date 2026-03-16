# Source: https://leetcode.com/problems/best-position-for-a-service-centre/   |   Difficulty: Hard
#
# Problem Description:
# A delivery company wants to build a new service center in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new center in a position such that the sum of the euclidean distances to all customers is minimum.
#
# Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.
#
# In other words, you need to choose the position of the service center [xcentre, ycentre] such that the following formula is minimized:
#
# Answers within 10-5 of the actual value will be accepted.
#
# Example:
# Input: positions = [[0,1],[1,0],[1,2],[2,1]]
# Output: 4.00000
# Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
#
# Constraints:
# 1 <= positions.length <= 50
# 	positions[i].length == 2
# 	0 <= xi, yi <= 100
#

class Solution(object):
    def getMinDistSum(self, positions):
        """
        :type positions: List[List[int]]
        :rtype: float
        """
        import random
        import math

        def dist(a, b):
            return math.sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2)

        def total_dist(point):
            return sum(dist(point, p) for p in positions)

        # Initial guess: centroid of the points
        x = sum(p[0] for p in positions) / len(positions)
        y = sum(p[1] for p in positions) / len(positions)
        center = [x, y]

        learning_rate = 100.0
        precision = 1e-6
        prev_dist = total_dist(center)

        while True:
            grad_x = sum((center[0] - p[0]) / dist(center, p) for p in positions)
            grad_y = sum((center[1] - p[1]) / dist(center, p) for p in positions)

            center[0] -= learning_rate * grad_x
            center[1] -= learning_rate * grad_y

            current_dist = total_dist(center)

            if abs(prev_dist - current_dist) < precision:
                break

            prev_dist = current_dist

        return current_dist