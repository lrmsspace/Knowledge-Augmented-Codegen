# Source: https://leetcode.com/problems/sliding-window-median/   |   Difficulty: Hard
#
# Problem Description:
# The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
#
#
# 	For examples, if arr = [2,3,4], the median is 3.
# 	For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
#
#
# You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
#
# Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
#
# Example:
# Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
# Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
# Explanation: 
# Window position                Median
# ---------------                -----
# [1  3  -1] -3  5  3  6  7        1
#  1 [3  -1  -3] 5  3  6  7       -1
#  1  3 [-1  -3  5] 3  6  7       -1
#  1  3  -1 [-3  5  3] 6  7        3
#  1  3  -1  -3 [5  3  6] 7        5
#  1  3  -1  -3  5 [3  6  7]       6
#
# Constraints:
# 1 <= k <= nums.length <= 105
# 	-231 <= nums[i] <= 231 - 1
#
# Helpful references (internal KB):
# -  
# Kth order statistic in O(N) (array, quickselect)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without fully sorting the entire data structure. It's particularly useful for large datasets where a full sort is too slow.
#   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list. It uses a divide-and-conquer approach similar to Quicksort, but only recurses on one side, achieving an average time complexity of O(N).
#   • Invariants: All elements to the left of the pivot are less than or equal to the pivot's value.; All elements to the right of the pivot are greater than or equal to the pivot's value.
#   • Tips: Choose a good pivot strategy, such as a random pivot, to minimize the chance of worst-case performance.; Handle duplicate elements carefully during the partitioning step to ensure correctness.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Deep recursion without tail call optimization can cause stack overflow errors.
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
#   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
#   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
#   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
#   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
#   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def medianSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[float]
        """
        from bisect import insort, bisect_left

        if not nums or k == 0:
            return []

        medians = []
        window = sorted(nums[:k])

        for i in range(k, len(nums) + 1):
            # Calculate median
            if k % 2 == 1:
                medians.append(float(window[k // 2]))
            else:
                medians.append((window[k // 2 - 1] + window[k // 2]) / 2.0)

            if i == len(nums):
                break

            # Remove the element going out of the window
            out_elem = nums[i - k]
            idx = bisect_left(window, out_elem)
            del window[idx]

            # Add the new element coming into the window
            insort(window, nums[i])

        return medians