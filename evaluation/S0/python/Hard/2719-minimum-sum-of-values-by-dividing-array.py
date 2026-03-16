# Source: https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given two arrays nums and andValues of length n and m respectively.
#
# The value of an array is equal to the last element of that array.
#
# You have to divide nums into m disjoint contiguous subarrays such that for the ith subarray [li, ri], the bitwise AND of the subarray elements is equal to andValues[i], in other words, nums[li] & nums[li + 1] & ... & nums[ri] == andValues[i] for all 1 <= i <= m, where & represents the bitwise AND operator.
#
# Return the minimum possible sum of the values of the m subarrays nums is divided into. If it is not possible to divide nums into m subarrays satisfying these conditions, return -1.
#
# Example:
# Input: nums = [1,4,3,3,2], andValues = [0,3,3,2]
#
# Output: 12
#
# Explanation:
#
# The only possible way to divide nums is:
#
#
# 	[1,4] as 1 & 4 == 0.
# 	[3] as the bitwise AND of a single element subarray is that element itself.
# 	[3] as the bitwise AND of a single element subarray is that element itself.
# 	[2] as the bitwise AND of a single element subarray is that element itself.
#
#
# The sum of the values for these subarrays is 4 + 3 + 3 + 2 = 12.
#
# Constraints:
# 1 <= n == nums.length <= 104
# 	1 <= m == andValues.length <= min(n, 10)
# 	1 <= nums[i] < 105
# 	0 <= andValues[j] < 105
#

class Solution(object):
    def minimumValueSum(self, nums, andValues):
        """
        :type nums: List[int]
        :type andValues: List[int]
        :rtype: int
        """
        n = len(nums)
        m = len(andValues)
        INF = float('inf')
        
        # dp[i][j]: minimum sum of values for first i elements divided into j subarrays
        dp = [[INF] * (m + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(1, min(i, m) + 1):
                current_and = (1 << 20) - 1  # Initialize to all bits set
                for k in range(i, 0, -1):
                    current_and &= nums[k - 1]
                    if current_and < andValues[j - 1]:
                        break
                    if current_and == andValues[j - 1]:
                        dp[i][j] = min(dp[i][j], dp[k - 1][j - 1] + nums[i - 1])
        
        return dp[n][m] if dp[n][m] != INF else -1