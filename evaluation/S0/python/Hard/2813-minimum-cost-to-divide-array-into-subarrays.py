# Source: https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integer arrays, nums and cost, of the same size, and an integer k.
#
# You can divide nums into subarrays. The cost of the ith subarray consisting of elements nums[l..r] is:
#
#
# 	(nums[0] + nums[1] + ... + nums[r] + k * i) * (cost[l] + cost[l + 1] + ... + cost[r]).
#
#
# Note that i represents the order of the subarray: 1 for the first subarray, 2 for the second, and so on.
#
# Return the minimum total cost possible from any valid division.
#
# Example:
# Input: nums = [3,1,4], cost = [4,6,6], k = 1
#
# Output: 110
#
# Explanation:
# The minimum total cost possible can be achieved by dividing nums into subarrays [3, 1] and [4].
#
#
# 	The cost of the first subarray [3,1] is (3 + 1 + 1 * 1) * (4 + 6) = 50.
# 	The cost of the second subarray [4] is (3 + 1 + 4 + 1 * 2) * 6 = 60.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	cost.length == nums.length
# 	1 <= nums[i], cost[i] <= 1000
# 	1 <= k <= 1000
#

class Solution(object):
    def minimumCost(self, nums, cost, k):
        """
        :type nums: List[int]
        :type cost: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        prefix_nums = [0] * (n + 1)
        prefix_cost = [0] * (n + 1)
        
        for i in range(n):
            prefix_nums[i + 1] = prefix_nums[i] + nums[i]
            prefix_cost[i + 1] = prefix_cost[i] + cost[i]
        
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            for j in range(i):
                subarray_cost = (prefix_nums[i] - prefix_nums[j] + k * (len(dp) - (j + 1))) * (prefix_cost[i] - prefix_cost[j])
                dp[i] = min(dp[i], dp[j] + subarray_cost)
        
        return dp[n]