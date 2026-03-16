# Source: https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are currently designing a dynamic array. You are given a 0-indexed integer array nums, where nums[i] is the number of elements that will be in the array at time i. In addition, you are given an integer k, the maximum number of times you can resize the array (to any size).
#
# The size of the array at time t, sizet, must be at least nums[t] because there needs to be enough space in the array to hold all the elements. The space wasted at time t is defined as sizet - nums[t], and the total space wasted is the sum of the space wasted across every time t where 0 <= t < nums.length.
#
# Return the minimum total space wasted if you can resize the array at most k times.
#
# Note: The array can have any size at the start and does not count towards the number of resizing operations.
#
# Example:
# Input: nums = [10,20], k = 0
# Output: 10
# Explanation: size = [20,20].
# We can set the initial size to be 20.
# The total wasted space is (20 - 10) + (20 - 20) = 10.
#
# Constraints:
# 1 <= nums.length <= 200
# 	1 <= nums[i] <= 106
# 	0 <= k <= nums.length - 1
#

class Solution(object):
    def minSpaceWastedKResizing(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]

        dp = [[float('inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            for j in range(k + 1):
                max_num = 0
                for p in range(i - 1, -1, -1):
                    max_num = max(max_num, nums[p])
                    if j > 0:
                        dp[i][j] = min(dp[i][j], dp[p][j - 1] + max_num * (i - p) - (prefix_sum[i] - prefix_sum[p]))
                    else:
                        dp[i][j] = min(dp[i][j], max_num * (i - p) - (prefix_sum[i] - prefix_sum[p]))

        return dp[n][k]