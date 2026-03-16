# Source: https://leetcode.com/problems/choose-k-elements-with-maximum-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays, nums1 and nums2, both of length n, along with a positive integer k.
#
# For each index i from 0 to n - 1, perform the following:
#
#
# 	Find all indices j where nums1[j] is less than nums1[i].
# 	Choose at most k values of nums2[j] at these indices to maximize the total sum.
#
#
# Return an array answer of size n, where answer[i] represents the result for the corresponding index i.
#
# Example:
# Input: nums1 = [4,2,1,5,3], nums2 = [10,20,30,40,50], k = 2
#
# Output: [80,30,0,80,50]
#
# Explanation:
#
#
# 	For i = 0: Select the 2 largest values from nums2 at indices [1, 2, 4] where nums1[j] < nums1[0], resulting in 50 + 30 = 80.
# 	For i = 1: Select the 2 largest values from nums2 at index [2] where nums1[j] < nums1[1], resulting in 30.
# 	For i = 2: No indices satisfy nums1[j] < nums1[2], resulting in 0.
# 	For i = 3: Select the 2 largest values from nums2 at indices [0, 1, 2, 4] where nums1[j] < nums1[3], resulting in 50 + 30 = 80.
# 	For i = 4: Select the 2 largest values from nums2 at indices [1, 2] where nums1[j] < nums1[4], resulting in 30 + 20 = 50.
#
# Constraints:
# n == nums1.length == nums2.length
# 	1 <= n <= 105
# 	1 <= nums1[i], nums2[i] <= 106
# 	1 <= k <= n
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
# - Elementary Sorts (array, enumeration)
#   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
#   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
#   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
#   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
#   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findMaxSum(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        import heapq

        n = len(nums1)
        result = [0] * n

        for i in range(n):
            smaller_nums2 = []
            for j in range(n):
                if nums1[j] < nums1[i]:
                    heapq.heappush(smaller_nums2, nums2[j])
                    if len(smaller_nums2) > k:
                        heapq.heappop(smaller_nums2)
            result[i] = sum(smaller_nums2)

        return result