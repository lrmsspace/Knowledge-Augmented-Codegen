# Source: https://leetcode.com/problems/zero-array-transformation-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].
#
# Each queries[i] represents the following action on nums:
#
#
# 	Decrement the value at each index in the range [li, ri] in nums by at most vali.
# 	The amount by which each value is decremented can be chosen independently for each index.
#
#
# A Zero Array is an array with all its elements equal to 0.
#
# Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
#
# Example:
# Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
#
# Output: 2
#
# Explanation:
#
#
# 	For i = 0 (l = 0, r = 2, val = 1):
#
# 	
# 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
# 		The array will become [1, 0, 1].
# 	
# 	
# 	For i = 1 (l = 0, r = 2, val = 1):
# 	
# 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
# 		The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 5 * 105
# 	1 <= queries.length <= 105
# 	queries[i].length == 3
# 	0 <= li <= ri < nums.length
# 	1 <= vali <= 5
#

class Solution(object):
    def minZeroArray(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: int
        """
        n = len(nums)
        left, right = 0, len(queries)

        def can_transform(k):
            diff = [0] * (n + 1)
            for i in range(k):
                l, r, val = queries[i]
                diff[l] += val
                diff[r + 1] -= val

            curr = 0
            for i in range(n):
                curr += diff[i]
                if curr < nums[i]:
                    return False
            return True

        result = -1
        while left <= right:
            mid = (left + right) // 2
            if can_transform(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1

        return result