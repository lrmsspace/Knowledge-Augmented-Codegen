# Source: https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary array nums and an integer k.
#
# A k-bit flip is choosing a subarray of length k from nums and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
#
# Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is not possible, return -1.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [0,1,0], k = 1
# Output: 2
# Explanation: Flip nums[0], then flip nums[2].
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= k <= nums.length
#

class Solution(object):
    def minKBitFlips(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        flip = [0] * (n + 1)
        current_flips = 0
        result = 0

        for i in range(n):
            current_flips ^= flip[i]
            if nums[i] ^ current_flips == 0:
                if i + k > n:
                    return -1
                result += 1
                current_flips ^= 1
                flip[i + k] ^= 1

        return result