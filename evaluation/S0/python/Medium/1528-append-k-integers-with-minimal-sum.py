# Source: https://leetcode.com/problems/append-k-integers-with-minimal-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer k. Append k unique positive integers that do not appear in nums to nums such that the resulting total sum is minimum.
#
# Return the sum of the k integers appended to nums.
#
# Example:
# Input: nums = [1,4,25,10,25], k = 2
# Output: 5
# Explanation: The two unique positive integers that do not appear in nums which we append are 2 and 3.
# The resulting sum of nums is 1 + 4 + 25 + 10 + 25 + 2 + 3 = 70, which is the minimum.
# The sum of the two integers appended is 2 + 3 = 5, so we return 5.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	1 <= k <= 108
#

class Solution(object):
    def minimalKSum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        nums = sorted(set(nums))
        res = 0
        prev = 0
        
        for num in nums:
            if k <= 0:
                break
            
            if num - prev - 1 > 0:
                count = min(k, num - prev - 1)
                res += (prev + 1 + prev + count) * count // 2
                k -= count
            
            prev = num
        
        if k > 0:
            res += (prev + 1 + prev + k) * k // 2
        
        return res