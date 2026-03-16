# Source: https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums consisting of positive integers. You can choose two indices i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of nums[j].
#
# Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and j that satisfy the conditions. If no such pair of indices exists, return -1.
#
# Example:
# Input: nums = [18,43,36,13,7]
# Output: 54
# Explanation: The pairs (i, j) that satisfy the conditions are:
# - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
# - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
# So the maximum sum that we can obtain is 54.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def maximumSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict

        digit_sum_map = defaultdict(list)

        for num in nums:
            digit_sum = sum(int(digit) for digit in str(num))
            digit_sum_map[digit_sum].append(num)

        max_sum = -1

        for num_list in digit_sum_map.values():
            if len(num_list) >= 2:
                num_list.sort(reverse=True)
                current_sum = num_list[0] + num_list[1]
                max_sum = max(max_sum, current_sum)

        return max_sum