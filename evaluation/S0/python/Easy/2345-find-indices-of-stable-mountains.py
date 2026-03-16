# Source: https://leetcode.com/problems/find-indices-of-stable-mountains/   |   Difficulty: Easy
#
# Problem Description:
# There are n mountains in a row, and each mountain has a height. You are given an integer array height where height[i] represents the height of mountain i, and an integer threshold.
#
# A mountain is called stable if the mountain just before it (if it exists) has a height strictly greater than threshold. Note that mountain 0 is not stable.
#
# Return an array containing the indices of all stable mountains in any order.
#
# Example:
# Input: height = [1,2,3,4,5], threshold = 2
#
# Output: [3,4]
#
# Explanation:
#
#
# 	Mountain 3 is stable because height[2] == 3 is greater than threshold == 2.
# 	Mountain 4 is stable because height[3] == 4 is greater than threshold == 2.
#
# Constraints:
# 2 <= n == height.length <= 100
# 	1 <= height[i] <= 100
# 	1 <= threshold <= 100
#

class Solution(object):
    def stableMountains(self, height, threshold):
        """
        :type height: List[int]
        :type threshold: int
        :rtype: List[int]
        """
        stable_indices = []
        for i in range(1, len(height)):
            if height[i - 1] > threshold:
                stable_indices.append(i)
        return stable_indices