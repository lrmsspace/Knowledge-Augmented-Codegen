# Source: https://leetcode.com/problems/zero-array-transformation-iii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri].
#
# Each queries[i] represents the following action on nums:
#
#
# 	Decrement the value at each index in the range [li, ri] in nums by at most 1.
# 	The amount by which the value is decremented can be chosen independently for each index.
#
#
# A Zero Array is an array with all its elements equal to 0.
#
# Return the maximum number of elements that can be removed from queries, such that nums can still be converted to a zero array using the remaining queries. If it is not possible to convert nums to a zero array, return -1.
#
# Example:
# Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
#
# Output: 1
#
# Explanation:
#
# After removing queries[2], nums can still be converted to a zero array.
#
#
# 	Using queries[0], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
# 	Using queries[1], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 105
# 	1 <= queries.length <= 105
# 	queries[i].length == 2
# 	0 <= li <= ri < nums.length
#

class Solution(object):
    def maxRemoval(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: int
        """
        n = len(nums)
        diff = [0] * (n + 1)

        for l, r in queries:
            diff[l] += 1
            diff[r + 1] -= 1

        for i in range(1, n):
            diff[i] += diff[i - 1]

        removals = 0
        for i in range(n):
            if diff[i] < nums[i]:
                return -1
            removals += diff[i] - nums[i]

        return removals