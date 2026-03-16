# Source: https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and two integers, x and k. You can perform the following operation any number of times (including zero):
#
#
# 	Increase or decrease any element of nums by 1.
#
#
# Return the minimum number of operations needed to have at least k non-overlapping subarrays of size exactly x in nums, where all elements within each subarray are equal.
#
# Example:
# Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2
#
# Output: 8
#
# Explanation:
#
#
# 	Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
# 	Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
# 	Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.
#
# Constraints:
# 2 <= nums.length <= 105
# 	-106 <= nums[i] <= 106
# 	2 <= x <= nums.length
# 	1 <= k <= 15
# 	2 <= k * x <= nums.length
#

class Solution(object):
    def minOperations(self, nums, x, k):
        """
        :type nums: List[int]
        :type x: int
        :type k: int
        :rtype: int
        """
        from collections import defaultdict
        import bisect

        n = len(nums)
        prefix_sums = [0] * (n + 1)
        for i in range(n):
            prefix_sums[i + 1] = prefix_sums[i] + nums[i]

        def cost(l, r):
            subarray = nums[l:r]
            subarray.sort()
            median = subarray[len(subarray) // 2]
            return sum(abs(num - median) for num in subarray)

        dp = [[float('inf')] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            for j in range(k + 1):
                dp[i][j] = dp[i - 1][j]
                if j > 0 and i >= x:
                    dp[i][j] = min(dp[i][j], dp[i - x][j - 1] + cost(i - x, i))

        return dp[n][k] if dp[n][k] != float('inf') else -1