# Source: https://leetcode.com/problems/minimum-moves-to-make-array-complementary/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.
#
# The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.
#
# Return the minimum number of moves required to make nums complementary.
#
# Example:
# Input: nums = [1,2,4,3], limit = 4
# Output: 1
# Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
# nums[0] + nums[3] = 1 + 3 = 4.
# nums[1] + nums[2] = 2 + 2 = 4.
# nums[2] + nums[1] = 2 + 2 = 4.
# nums[3] + nums[0] = 3 + 1 = 4.
# Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
#
# Constraints:
# n == nums.length
# 	2 <= n <= 105
# 	1 <= nums[i] <= limit <= 105
# 	n is even.
#

class Solution(object):
    def minMoves(self, nums, limit):
        """
        :type nums: List[int]
        :type limit: int
        :rtype: int
        """
        n = len(nums)
        diff = [0] * (2 * limit + 2)

        for i in range(n // 2):
            a = nums[i]
            b = nums[n - 1 - i]
            low = min(a, b) + 1
            high = max(a, b) + limit

            diff[2] += 2
            diff[low] -= 1
            diff[a + b] -= 1
            diff[a + b + 1] += 1
            diff[high + 1] += 1

        min_moves = float('inf')
        current_moves = 0

        for x in range(2, 2 * limit + 1):
            current_moves += diff[x]
            min_moves = min(min_moves, current_moves)

        return min_moves