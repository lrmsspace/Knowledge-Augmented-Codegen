# Source: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.
#
# Example:
# Input: nums = [4,3,2,3,5,2,1], k = 4
# Output: true
# Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
#
# Constraints:
# 1 <= k <= nums.length <= 16
# 	1 <= nums[i] <= 104
# 	The frequency of each element is in the range [1, 4].
#

class Solution(object):
    def canPartitionKSubsets(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        total_sum = sum(nums)
        if total_sum % k != 0:
            return False
        
        target = total_sum // k
        nums.sort(reverse=True)
        used = [False] * len(nums)
        
        def backtrack(start_index, number_of_subsets, current_sum):
            if number_of_subsets == 0:
                return True
            if current_sum == target:
                return backtrack(0, number_of_subsets - 1, 0)
            
            for i in range(start_index, len(nums)):
                if used[i] or current_sum + nums[i] > target:
                    continue
                
                used[i] = True
                if backtrack(i + 1, number_of_subsets, current_sum + nums[i]):
                    return True
                used[i] = False
            
            return False
        
        return backtrack(0, k, 0)