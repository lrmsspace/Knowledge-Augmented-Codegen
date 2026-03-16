# Source: https://leetcode.com/problems/maximum-sum-of-almost-unique-subarray/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and two positive integers m and k.
#
# Return the maximum sum out of all almost unique subarrays of length k of nums. If no such subarray exists, return 0.
#
# A subarray of nums is almost unique if it contains at least m distinct elements.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [2,6,7,3,1,7], m = 3, k = 4
# Output: 18
# Explanation: There are 3 almost unique subarrays of size k = 4. These subarrays are [2, 6, 7, 3], [6, 7, 3, 1], and [7, 3, 1, 7]. Among these subarrays, the one with the maximum sum is [2, 6, 7, 3] which has a sum of 18.
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	1 <= m <= k <= nums.length
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def maxSum(self, nums, m, k):
        """
        :type nums: List[int]
        :type m: int
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        n = len(nums)
        if k > n:
            return 0

        count = defaultdict(int)
        current_sum = 0
        max_sum = 0

        # Initialize the first window
        for i in range(k):
            count[nums[i]] += 1
            current_sum += nums[i]

        if len(count) >= m:
            max_sum = current_sum

        # Slide the window
        for i in range(k, n):
            count[nums[i]] += 1
            current_sum += nums[i]

            count[nums[i - k]] -= 1
            current_sum -= nums[i - k]
            if count[nums[i - k]] == 0:
                del count[nums[i - k]]

            if len(count) >= m:
                max_sum = max(max_sum, current_sum)

        return max_sum