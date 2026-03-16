# Source: https://leetcode.com/problems/count-special-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of positive integers.
#
# A special subsequence is defined as a subsequence of length 4, represented by indices (p, q, r, s), where p < q < r < s. This subsequence must satisfy the following conditions:
#
#
#  nums[p] * nums[r] == nums[q] * nums[s]
#  There must be at least one element between each pair of indices. In other words, q - p > 1, r - q > 1 and s - r > 1.
#
#
# Return the number of different special subsequences in nums.
#
# Example:
# Input: nums = [1,2,3,4,3,6,1]
#
# Output: 1
#
# Explanation:
#
# There is one special subsequence in nums.
#
#
#  (p, q, r, s) = (0, 2, 4, 6):
#
#  
#   This corresponds to elements (1, 3, 3, 1).
#   nums[p] * nums[r] = nums[0] * nums[4] = 1 * 3 = 3
#   nums[q] * nums[s] = nums[2] * nums[6] = 3 * 1 = 3
#
# Constraints:
# 7 <= nums.length <= 1000
#  1 <= nums[i] <= 1000
#

class Solution(object):
    def numberOfSubsequences(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict

        n = len(nums)
        count = 0
        pair_count = defaultdict(int)

        for j in range(1, n - 2):
            for i in range(j - 1):
                product = nums[i] * nums[j]
                pair_count[product] += 1

            for k in range(j + 2, n):
                product = nums[j] * nums[k]
                if product in pair_count:
                    count += pair_count[product]

        return count