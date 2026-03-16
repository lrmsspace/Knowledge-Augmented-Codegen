# Source: https://leetcode.com/problems/apply-operations-to-maximize-frequency-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums and an integer k.
#
# You can perform the following operation on the array at most k times:
#
#
# 	Choose any index i from the array and increase or decrease nums[i] by 1.
#
#
# The score of the final array is the frequency of the most frequent element in the array.
#
# Return the maximum score you can achieve.
#
# The frequency of an element is the number of occurences of that element in the array.
#
# Example:
# Input: nums = [1,2,6,4], k = 3
# Output: 3
# Explanation: We can do the following operations on the array:
# - Choose i = 0, and increase the value of nums[0] by 1. The resulting array is [2,2,6,4].
# - Choose i = 3, and decrease the value of nums[3] by 1. The resulting array is [2,2,6,3].
# - Choose i = 3, and decrease the value of nums[3] by 1. The resulting array is [2,2,6,2].
# The element 2 is the most frequent in the final array so our score is 3.
# It can be shown that we cannot achieve a better score.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	0 <= k <= 1014
#
# Helpful references (internal KB):
# - Mergesort (array, merge-sort, divide-and-conquer, recursion)
#   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
#   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
#   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
#   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
#   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
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
    def maxFrequencyScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        nums.sort()
        left = 0
        total = 0
        max_freq = 1

        for right in range(len(nums)):
            total += nums[right]

            while (right - left + 1) * nums[right] - total > k:
                total -= nums[left]
                left += 1

            max_freq = max(max_freq, right - left + 1)

        return max_freq