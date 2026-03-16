# Source: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums consisting of 3 * n elements.
#
# You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:
#
#
# 	The first n elements belonging to the first part and their sum is sumfirst.
# 	The next n elements belonging to the second part and their sum is sumsecond.
#
#
# The difference in sums of the two parts is denoted as sumfirst - sumsecond.
#
#
# 	For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
# 	Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
#
#
# Return the minimum difference possible between the sums of the two parts after the removal of n elements.
#
# Example:
# Input: nums = [3,1,2]
# Output: -1
# Explanation: Here, nums has 3 elements, so n = 1. 
# Thus we have to remove 1 element from nums and divide the array into two equal parts.
# - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
# - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
# - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
# The minimum difference between sums of the two parts is min(-1,1,2) = -1.
#
# Constraints:
# nums.length == 3 * n
# 	1 <= n <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def minimumDifference(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        import heapq

        n = len(nums) // 3

        left_heap = []
        left_sum = [0] * (n + 1)
        current_sum = 0

        for i in range(n):
            current_sum += nums[i]
            heapq.heappush(left_heap, -nums[i])
        left_sum[0] = current_sum

        for i in range(n, 2 * n):
            current_sum += nums[i]
            heapq.heappush(left_heap, -nums[i])
            removed = -heapq.heappop(left_heap)
            current_sum -= removed
            left_sum[i - n + 1] = current_sum

        right_heap = []
        right_sum = [0] * (n + 1)
        current_sum = 0

        for i in range(3 * n - 1, 2 * n - 1, -1):
            current_sum += nums[i]
            heapq.heappush(right_heap, nums[i])
        right_sum[n] = current_sum

        for i in range(2 * n - 1, n - 1, -1):
            current_sum += nums[i]
            heapq.heappush(right_heap, nums[i])
            removed = heapq.heappop(right_heap)
            current_sum -= removed
            right_sum[i - n] = current_sum

        min_diff = float('inf')
        for i in range(n + 1):
            min_diff = min(min_diff, left_sum[i] - right_sum[i])

        return min_diff