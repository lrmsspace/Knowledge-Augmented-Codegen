# Source: https://leetcode.com/problems/ways-to-split-array-into-good-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary array nums.
#
# A subarray of an array is good if it contains exactly one element with the value 1.
#
# Return an integer denoting the number of ways to split the array nums into good subarrays. As the number may be too large, return it modulo 109 + 7.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [0,1,0,0,1]
# Output: 3
# Explanation: There are 3 ways to split nums into good subarrays:
# - [0,1] [0,0,1]
# - [0,1,0] [0,1]
# - [0,1,0,0] [1]
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 1
#

class Solution(object):
    def numberOfGoodSubarraySplits(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        result = 1
        count = 0
        found_one = False

        for num in nums:
            if num == 1:
                if found_one:
                    result = (result * (count + 1)) % MOD
                found_one = True
                count = 0
            else:
                if found_one:
                    count += 1

        return result if found_one else 0