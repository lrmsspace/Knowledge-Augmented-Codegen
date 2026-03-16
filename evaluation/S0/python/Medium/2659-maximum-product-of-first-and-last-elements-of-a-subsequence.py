# Source: https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer m.
#
# Return the maximum product of the first and last elements of any subsequence of nums of size m.
#
# Example:
# Input: nums = [-1,-9,2,3,-2,-3,1], m = 1
#
# Output: 81
#
# Explanation:
#
# The subsequence [-9] has the largest product of the first and last elements: -9 * -9 = 81. Therefore, the answer is 81.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-105 <= nums[i] <= 105
# 	1 <= m <= nums.length
#

class Solution(object):
    def maximumProduct(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        nums.sort()
        max_product = float('-inf')
        
        # Check the product of the first and last elements in the subsequence
        for i in range(len(nums) - m + 1):
            first = nums[i]
            last = nums[i + m - 1]
            product = first * last
            max_product = max(max_product, product)
        
        return max_product