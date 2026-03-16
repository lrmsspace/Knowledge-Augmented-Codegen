# Source: https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.
#
# Return the minimum number of moves required so that nums has k consecutive 1's.
#
# Example:
# Input: nums = [1,0,0,1,0,1], k = 2
# Output: 1
# Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
#
# Constraints:
# 1 <= nums.length <= 105
# 	nums[i] is 0 or 1.
# 	1 <= k <= sum(nums)
#

class Solution(object):
    def minMoves(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        ones = [i for i, num in enumerate(nums) if num == 1]
        prefix_sum = [0]
        for index in ones:
            prefix_sum.append(prefix_sum[-1] + index)

        min_moves = float('inf')
        for i in range(len(ones) - k + 1):
            mid = i + k // 2
            median = ones[mid]
            left_count = mid - i
            right_count = i + k - mid - 1

            left_sum = prefix_sum[mid] - prefix_sum[i]
            right_sum = prefix_sum[i + k] - prefix_sum[mid + 1]

            moves = (median * left_count - left_sum) + (right_sum - median * right_count)

            if k % 2 == 0:
                moves -= left_count

            min_moves = min(min_moves, moves)

        return min_moves