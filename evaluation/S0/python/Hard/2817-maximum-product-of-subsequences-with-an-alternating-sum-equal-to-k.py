# Source: https://leetcode.com/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and two integers, k and limit. Your task is to find a non-empty subsequence of nums that:
#
#
# 	Has an alternating sum equal to k.
# 	Maximizes the product of all its numbers without the product exceeding limit.
#
#
# Return the product of the numbers in such a subsequence. If no subsequence satisfies the requirements, return -1.
#
# The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the sum of the elements at odd indices.
#
# Example:
# Input: nums = [1,2,3], k = 2, limit = 10
#
# Output: 6
#
# Explanation:
#
# The subsequences with an alternating sum of 2 are:
#
#
# 	[1, 2, 3]
#
# 	
# 		Alternating Sum: 1 - 2 + 3 = 2
# 		Product: 1 * 2 * 3 = 6
# 	
# 	
# 	[2]
# 	
# 		Alternating Sum: 2
# 		Product: 2
# 	
# 	
#
#
# The maximum product within the limit is 6.
#
# Constraints:
# 1 <= nums.length <= 150
# 	0 <= nums[i] <= 12
# 	-105 <= k <= 105
# 	1 <= limit <= 5000
#

class Solution(object):
    def maxProduct(self, nums, k, limit):
        """
        :type nums: List[int]
        :type k: int
        :type limit: int
        :rtype: int
        """
        n = len(nums)
        dp = [[[-1] * (limit + 1) for _ in range(2 * 10**5 + 1)] for _ in range(n + 1)]
        offset = 10**5
        dp[0][offset][0] = 1

        for i in range(1, n + 1):
            num = nums[i - 1]
            for s in range(-10**5, 10**5 + 1):
                for p in range(limit + 1):
                    if dp[i - 1][s + offset][p] != -1:
                        dp[i][s + offset][p] = max(dp[i][s + offset][p], dp[i - 1][s + offset][p])
                        new_s = s + num if i % 2 == 1 else s - num
                        new_p = p * num
                        if new_p <= limit:
                            dp[i][new_s + offset][new_p] = max(dp[i][new_s + offset][new_p], dp[i - 1][s + offset][p] * num)

        max_product = -1
        for p in range(limit + 1):
            max_product = max(max_product, dp[n][k + offset][p])

        return max_product