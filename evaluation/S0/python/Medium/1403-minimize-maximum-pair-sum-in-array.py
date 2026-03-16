# Source: https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/   |   Difficulty: Medium
#
# Problem Description:
# The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the largest pair sum in a list of pairs.
#
#
# 	For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.
#
#
# Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:
#
#
# 	Each element of nums is in exactly one pair, and
# 	The maximum pair sum is minimized.
#
#
# Return the minimized maximum pair sum after optimally pairing up the elements.
#
# Example:
# Input: nums = [3,5,2,3]
# Output: 7
# Explanation: The elements can be paired up into pairs (3,3) and (5,2).
# The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.
#
# Constraints:
# n == nums.length
# 	2 <= n <= 105
# 	n is even.
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def minPairSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        left, right = 0, len(nums) - 1
        max_pair_sum = 0

        while left < right:
            pair_sum = nums[left] + nums[right]
            max_pair_sum = max(max_pair_sum, pair_sum)
            left += 1
            right -= 1

        return max_pair_sum