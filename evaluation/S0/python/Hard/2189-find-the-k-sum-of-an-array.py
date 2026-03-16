# Source: https://leetcode.com/problems/find-the-k-sum-of-an-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and a positive integer k. You can choose any subsequence of the array and sum all of its elements together.
#
# We define the K-Sum of the array as the kth largest subsequence sum that can be obtained (not necessarily distinct).
#
# Return the K-Sum of the array.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Note that the empty subsequence is considered to have a sum of 0.
#
# Example:
# Input: nums = [2,4,-2], k = 5
# Output: 2
# Explanation: All the possible subsequence sums that we can obtain are the following sorted in decreasing order:
# 6, 4, 4, 2, 2, 0, 0, -2.
# The 5-Sum of the array is 2.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 105
# 	-109 <= nums[i] <= 109
# 	1 <= k <= min(2000, 2n)
#

class Solution(object):
    def kSum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        import heapq

        max_heap = []
        total_sum = 0

        for num in nums:
            if num > 0:
                total_sum += num

        heapq.heappush(max_heap, (-total_sum, 0))
        visited = set((0,))

        for _ in range(k):
            current_sum, index = heapq.heappop(max_heap)
            current_sum = -current_sum

            if index == len(nums):
                continue

            next_index = index + 1

            # Exclude nums[index]
            new_sum_exclude = current_sum - max(0, nums[index])
            if next_index not in visited:
                heapq.heappush(max_heap, (-new_sum_exclude, next_index))
                visited.add(next_index)

            # Include nums[index]
            new_sum_include = current_sum
            if next_index not in visited:
                heapq.heappush(max_heap, (-new_sum_include, next_index))
                visited.add(next_index)

        return current_sum