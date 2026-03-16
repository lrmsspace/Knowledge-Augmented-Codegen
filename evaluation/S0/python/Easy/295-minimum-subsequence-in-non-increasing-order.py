# Source: https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/   |   Difficulty: Easy
#
# Problem Description:
# Given the array nums, obtain a subsequence of the array whose sum of elements is strictly greater than the sum of the non included elements in such subsequence. 
#
# If there are multiple solutions, return the subsequence with minimum size and if there still exist multiple solutions, return the subsequence with the maximum total sum of all its elements. A subsequence of an array can be obtained by erasing some (possibly zero) elements from the array. 
#
# Note that the solution with the given constraints is guaranteed to be unique. Also return the answer sorted in non-increasing order.
#
# Example:
# Input: nums = [4,3,10,9,8]
# Output: [10,9] 
# Explanation: The subsequences [10,9] and [10,8] are minimal such that the sum of their elements is strictly greater than the sum of elements not included. However, the subsequence [10,9] has the maximum total sum of its elements.
#
# Constraints:
# 1 <= nums.length <= 500
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def minSubsequence(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        nums.sort(reverse=True)
        total = sum(nums)
        subseq = []
        subseq_sum = 0
        
        for num in nums:
            subseq.append(num)
            subseq_sum += num
            if subseq_sum > total - subseq_sum:
                return subseq
        return subseq