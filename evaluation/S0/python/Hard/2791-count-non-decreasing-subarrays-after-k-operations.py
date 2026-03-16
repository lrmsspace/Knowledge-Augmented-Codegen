# Source: https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of n integers and an integer k.
#
# For each subarray of nums, you can apply up to k operations on it. In each operation, you increment any element of the subarray by 1.
#
# Note that each subarray is considered independently, meaning changes made to one subarray do not persist to another.
#
# Return the number of subarrays that you can make non-decreasing ​​​​​after performing at most k operations.
#
# An array is said to be non-decreasing if each element is greater than or equal to its previous element, if it exists.
#
# Example:
# Input: nums = [6,3,1,2,4,4], k = 7
#
# Output: 17
#
# Explanation:
#
# Out of all 21 possible subarrays of nums, only the subarrays [6, 3, 1], [6, 3, 1, 2], [6, 3, 1, 2, 4] and [6, 3, 1, 2, 4, 4] cannot be made non-decreasing after applying up to k = 7 operations. Thus, the number of non-decreasing subarrays is 21 - 4 = 17.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	1 <= k <= 109
#

class Solution(object):
    def countNonDecreasingSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        total_subarrays = n * (n + 1) // 2
        
        def can_make_non_decreasing(length):
            operations_needed = 0
            for i in range(1, length):
                if nums[i] < nums[i - 1]:
                    operations_needed += nums[i - 1] - nums[i]
            return operations_needed <= k
        
        left, right = 1, n
        while left <= right:
            mid = (left + right) // 2
            if can_make_non_decreasing(mid):
                left = mid + 1
            else:
                right = mid - 1
        
        valid_length = right
        invalid_subarrays = 0
        
        for length in range(valid_length + 1, n + 1):
            invalid_subarrays += (n - length + 1)
        
        return total_subarrays - invalid_subarrays