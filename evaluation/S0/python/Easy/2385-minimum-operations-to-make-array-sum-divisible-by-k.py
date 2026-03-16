# Source: https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums and an integer k. You can perform the following operation any number of times:
#
#
# 	Select an index i and replace nums[i] with nums[i] - 1.
#
#
# Return the minimum number of operations required to make the sum of the array divisible by k.
#
# Example:
# Input: nums = [3,9,7], k = 5
#
# Output: 4
#
# Explanation:
#
#
# 	Perform 4 operations on nums[1] = 9. Now, nums = [3, 5, 7].
# 	The sum is 15, which is divisible by 5.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 1000
# 	1 <= k <= 100
#

class Solution(object):
    def minOperations(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        total_sum = sum(nums)
        remainder = total_sum % k
        
        if remainder == 0:
            return 0
        
        min_operations = float('inf')
        
        for num in nums:
            mod_value = num % k
            if mod_value >= remainder:
                operations = mod_value - remainder
            else:
                operations = mod_value + (k - remainder)
            
            min_operations = min(min_operations, operations)
        
        return min_operations