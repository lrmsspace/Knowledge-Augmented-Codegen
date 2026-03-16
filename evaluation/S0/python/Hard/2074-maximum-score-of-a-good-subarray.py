# Source: https://leetcode.com/problems/maximum-score-of-a-good-subarray/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of integers nums (0-indexed) and an integer k.
#
# The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1). A good subarray is a subarray where i <= k <= j.
#
# Return the maximum possible score of a good subarray.
#
# Example:
# Input: nums = [1,4,3,7,4,5], k = 3
# Output: 15
# Explanation: The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) * (5-1+1) = 3 * 5 = 15.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 2 * 104
# 	0 <= k < nums.length
#

class Solution(object):
    def maximumScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        left = right = k
        min_height = nums[k]
        max_score = min_height

        while left > 0 or right < len(nums) - 1:
            if right < len(nums) - 1 and (left == 0 or nums[right + 1] >= nums[left - 1]):
                right += 1
                min_height = min(min_height, nums[right])
            else:
                left -= 1
                min_height = min(min_height, nums[left])

            current_score = min_height * (right - left + 1)
            max_score = max(max_score, current_score)

        return max_score