# Source: https://leetcode.com/problems/count-number-of-nice-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
#
# Return the number of nice sub-arrays.
#
# Example:
# Input: nums = [1,1,2,1,1], k = 3
# Output: 2
# Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
#
# Constraints:
# 1 <= nums.length <= 50000
# 	1 <= nums[i] <= 10^5
# 	1 <= k <= nums.length
#

class Solution(object):
    def numberOfSubarrays(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        count = 0
        odd_indices = [-1]  # Initialize with -1 to handle the left boundary

        # Collect indices of odd numbers
        for i, num in enumerate(nums):
            if num % 2 == 1:
                odd_indices.append(i)

        odd_indices.append(len(nums))  # Append length to handle the right boundary

        # Calculate the number of nice subarrays
        for i in range(1, len(odd_indices) - k):
            left_even_count = odd_indices[i] - odd_indices[i - 1]
            right_even_count = odd_indices[i + k] - odd_indices[i + k - 1]
            count += left_even_count * right_even_count

        return count