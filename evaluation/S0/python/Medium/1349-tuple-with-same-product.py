# Source: https://leetcode.com/problems/tuple-with-same-product/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.
#
# Example:
# Input: nums = [2,3,4,6]
# Output: 8
# Explanation: There are 8 valid tuples:
# (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
# (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 104
# 	All elements in nums are distinct.
#

class Solution(object):
    def tupleSameProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict
        product_count = defaultdict(int)
        
        # Count the occurrences of each product
        n = len(nums)
        for i in range(n):
            for j in range(i + 1, n):
                product = nums[i] * nums[j]
                product_count[product] += 1
        
        # Calculate the number of tuples based on the counts
        result = 0
        for count in product_count.values():
            if count > 1:
                result += count * (count - 1)  # Each pair can form 2 tuples
        
        return result