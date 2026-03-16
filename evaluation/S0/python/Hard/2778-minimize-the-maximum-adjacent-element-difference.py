# Source: https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of integers nums. Some values in nums are missing and are denoted by -1.
#
# You must choose a pair of positive integers (x, y) exactly once and replace each missing element with either x or y.
#
# You need to minimize the maximum absolute difference between adjacent elements of nums after replacements.
#
# Return the minimum possible difference.
#
# Example:
# Input: nums = [1,2,-1,10,8]
#
# Output: 4
#
# Explanation:
#
# By choosing the pair as (6, 7), nums can be changed to [1, 2, 6, 10, 8].
#
# The absolute differences between adjacent elements are:
#
#
# 	|1 - 2| == 1
# 	|2 - 6| == 4
# 	|6 - 10| == 4
# 	|10 - 8| == 2
#
# Constraints:
# 2 <= nums.length <= 105
# 	nums[i] is either -1 or in the range [1, 109].
#

class Solution(object):
    def minDifference(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        left, right = 1, 10**9
        adjacent = []

        for i in range(n):
            if nums[i] != -1:
                if i > 0 and nums[i-1] == -1:
                    adjacent.append(nums[i])
                if i < n-1 and nums[i+1] == -1:
                    adjacent.append(nums[i])

        if not adjacent:
            max_diff = 0
            for i in range(1, n):
                max_diff = max(max_diff, abs(nums[i] - nums[i-1]))
            return max_diff, 1

        min_adjacent = min(adjacent)
        max_adjacent = max(adjacent)

        while left < right:
            mid = (left + right) // 2
            k_min = max(1, max_adjacent - mid)
            k_max = min(10**9, min_adjacent + mid)

            if k_min <= k_max:
                right = mid
            else:
                left = mid + 1

        k_min = max(1, max_adjacent - left)
        k_max = min(10**9, min_adjacent + left)
        k = (k_min + k_max) // 2

        max_diff = 0
        prev = None
        for num in nums:
            if num == -1:
                num = k
            if prev is not None:
                max_diff = max(max_diff, abs(num - prev))
            prev = num

        return max_diff, k