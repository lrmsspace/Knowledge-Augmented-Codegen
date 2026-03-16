# Source: https://leetcode.com/problems/maximum-building-height/   |   Difficulty: Hard
#
# Problem Description:
# You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.
#
# However, there are city restrictions on the heights of the new buildings:
#
#
# 	The height of each building must be a non-negative integer.
# 	The height of the first building must be 0.
# 	The height difference between any two adjacent buildings cannot exceed 1.
#
#
# Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.
#
# It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.
#
# Return the maximum possible height of the tallest building.
#
# Example:
# Input: n = 5, restrictions = [[2,1],[4,1]]
# Output: 2
# Explanation: The green area in the image indicates the maximum allowed height for each building.
# We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
#
# Constraints:
# 2 <= n <= 109
# 	0 <= restrictions.length <= min(n - 1, 105)
# 	2 <= idi <= n
# 	idi is unique.
# 	0 <= maxHeighti <= 109
#

class Solution(object):
    def maxBuilding(self, n, restrictions):
        """
        :type n: int
        :type restrictions: List[List[int]]
        :rtype: int
        """
        restrictions.append([1, 0])
        restrictions.append([n, n - 1])
        restrictions.sort()
        
        for i in range(1, len(restrictions)):
            prev_id, prev_max = restrictions[i - 1]
            curr_id, curr_max = restrictions[i]
            restrictions[i][1] = min(curr_max, prev_max + (curr_id - prev_id))
        
        for i in range(len(restrictions) - 2, -1, -1):
            next_id, next_max = restrictions[i + 1]
            curr_id, curr_max = restrictions[i]
            restrictions[i][1] = min(curr_max, next_max + (next_id - curr_id))
        
        max_height = 0
        for i in range(1, len(restrictions)):
            prev_id, prev_max = restrictions[i - 1]
            curr_id, curr_max = restrictions[i]
            distance = curr_id - prev_id
            height_diff = abs(curr_max - prev_max)
            if distance < height_diff:
                continue
            peak_height = (distance - height_diff) // 2 + max(prev_max, curr_max)
            max_height = max(max_height, peak_height)
        
        return max_height