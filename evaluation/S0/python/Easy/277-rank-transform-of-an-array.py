# Source: https://leetcode.com/problems/rank-transform-of-an-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of integers arr, replace each element with its rank.
#
# The rank represents how large the element is. The rank has the following rules:
#
#
# 	Rank is an integer starting from 1.
# 	The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
# 	Rank should be as small as possible.
#
# Example:
# Input: arr = [40,10,20,30]
# Output: [4,1,2,3]
# Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.
#
# Constraints:
# 0 <= arr.length <= 105
# 	-109 <= arr[i] <= 109
#

class Solution(object):
    def arrayRankTransform(self, arr):
        """
        :type arr: List[int]
        :rtype: List[int]
        """
        sorted_unique = sorted(set(arr))
        rank_map = {value: rank + 1 for rank, value in enumerate(sorted_unique)}
        return [rank_map[num] for num in arr]