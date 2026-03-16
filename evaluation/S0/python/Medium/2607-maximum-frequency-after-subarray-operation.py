# Source: https://leetcode.com/problems/maximum-frequency-after-subarray-operation/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums of length n. You are also given an integer k.
#
# You perform the following operation on nums once:
#
#
# 	Select a subarray nums[i..j] where 0 <= i <= j <= n - 1.
# 	Select an integer x and add x to all the elements in nums[i..j].
#
#
# Find the maximum frequency of the value k after the operation.
#
# Example:
# Input: nums = [1,2,3,4,5,6], k = 1
#
# Output: 2
#
# Explanation:
#
# After adding -5 to nums[2..5], 1 has a frequency of 2 in [1, 2, -2, -1, 0, 1].
#
# Constraints:
# 1 <= n == nums.length <= 105
# 	1 <= nums[i] <= 50
# 	1 <= k <= 50
#

class Solution(object):
    def maxFrequency(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        count = [0] * 51
        for num in nums:
            count[num] += 1
        
        max_freq = count[k]
        current_freq = max_freq
        
        for diff in range(1, 51):
            if k - diff >= 1:
                current_freq += count[k - diff]
            if k + diff <= 50:
                current_freq -= count[k + diff]
            max_freq = max(max_freq, current_freq)
        
        return max_freq