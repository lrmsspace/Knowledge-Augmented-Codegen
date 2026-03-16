# Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
# A subsequence sub of nums with length x is called valid if it satisfies:
#
#
# 	(sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
#
#
# Return the length of the longest valid subsequence of nums.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [1,2,3,4]
#
# Output: 4
#
# Explanation:
#
# The longest valid subsequence is [1, 2, 3, 4].
#
# Constraints:
# 2 <= nums.length <= 2 * 105
# 	1 <= nums[i] <= 107
#

class Solution(object):
    def maximumLength(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n < 2:
            return n
        
        max_length = 1
        current_length = 1
        
        for i in range(1, n):
            if (nums[i] + nums[i - 1]) % 2 == (nums[i - 1] + nums[i - 2]) % 2:
                current_length += 1
            else:
                current_length = 2
            
            max_length = max(max_length, current_length)
        
        return max_length