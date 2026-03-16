# Source: https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-i/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums, find the number of subsequences of size 5 of nums with a unique middle mode.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# A mode of a sequence of numbers is defined as the element that appears the maximum number of times in the sequence.
#
# A sequence of numbers contains a unique mode if it has only one mode.
#
# A sequence of numbers seq of size 5 contains a unique middle mode if the middle element (seq[2]) is a unique mode.
#
# Example:
# Input: nums = [1,1,1,1,1,1]
#
# Output: 6
#
# Explanation:
#
# [1, 1, 1, 1, 1] is the only subsequence of size 5 that can be formed, and it has a unique middle mode of 1. This subsequence can be formed in 6 different ways, so the output is 6.
#
# Constraints:
# 5 <= nums.length <= 1000
#  -109 <= nums[i] <= 109
#

class Solution(object):
    def subsequencesWithMiddleMode(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        result = 0

        for mid in range(2, n - 2):
            count_left = {}
            count_right = {}

            for i in range(mid):
                count_left[nums[i]] = count_left.get(nums[i], 0) + 1

            for i in range(mid + 1, n):
                count_right[nums[i]] = count_right.get(nums[i], 0) + 1

            left_combinations = {}
            right_combinations = {}

            for num, cnt in count_left.items():
                for k in range(1, min(cnt, 2) + 1):
                    left_combinations[(num, k)] = left_combinations.get((num, k), 0) + self.nCr(cnt, k)

            for num, cnt in count_right.items():
                for k in range(1, min(cnt, 2) + 1):
                    right_combinations[(num, k)] = right_combinations.get((num, k), 0) + self.nCr(cnt, k)

            for (num_l, k_l), ways_l in left_combinations.items():
                for (num_r, k_r), ways_r in right_combinations.items():
                    if num_l == nums[mid] and k_l + (1 if num_r == nums[mid] else 0) >= 2:
                        continue
                    if num_r == nums[mid] and k_r + (1 if num_l == nums[mid] else 0) >= 2:
                        continue
                    result = (result + ways_l * ways_r) % MOD

        return result