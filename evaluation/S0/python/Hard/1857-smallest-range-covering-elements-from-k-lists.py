# Source: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/   |   Difficulty: Hard
#
# Problem Description:
# You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
#
# We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
#
# Example:
# Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
# Output: [20,24]
# Explanation: 
# List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
# List 2: [0, 9, 12, 20], 20 is in range [20,24].
# List 3: [5, 18, 22, 30], 22 is in range [20,24].
#
# Constraints:
# nums.length == k
# 	1 <= k <= 3500
# 	1 <= nums[i].length <= 50
# 	-105 <= nums[i][j] <= 105
# 	nums[i] is sorted in non-decreasing order.
#

class Solution(object):
    def smallestRange(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: List[int]
        """
        import heapq

        min_heap = []
        current_max = float('-inf')

        # Initialize the heap with the first element of each list
        for i in range(len(nums)):
            heapq.heappush(min_heap, (nums[i][0], i, 0))
            current_max = max(current_max, nums[i][0])

        best_range = [float('-inf'), float('inf')]

        while True:
            current_min, list_idx, elem_idx = heapq.heappop(min_heap)

            # Update the best range if the current range is smaller
            if current_max - current_min < best_range[1] - best_range[0]:
                best_range = [current_min, current_max]

            # If there is a next element in the same list, add it to the heap
            if elem_idx + 1 < len(nums[list_idx]):
                next_elem = nums[list_idx][elem_idx + 1]
                heapq.heappush(min_heap, (next_elem, list_idx, elem_idx + 1))
                current_max = max(current_max, next_elem)
            else:
                break  # One of the lists is exhausted

        return best_range