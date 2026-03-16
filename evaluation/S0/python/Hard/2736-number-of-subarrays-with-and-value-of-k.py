# Source: https://leetcode.com/problems/number-of-subarrays-with-and-value-of-k/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of integers nums and an integer k, return the number of subarrays of nums where the bitwise AND of the elements of the subarray equals k.
#
# Example:
# Input: nums = [1,1,1], k = 1
#
# Output: 6
#
# Explanation:
#
# All subarrays contain only 1's.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i], k <= 109
#

class Solution(object):
    def countSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        count = 0
        
        for i in range(n):
            current_and = nums[i]
            if current_and == k:
                count += 1
            
            for j in range(i + 1, n):
                current_and &= nums[j]
                if current_and == k:
                    count += 1
                elif current_and < k:
                    break
        
        return count