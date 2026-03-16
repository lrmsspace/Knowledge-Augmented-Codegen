# Source: https://leetcode.com/problems/largest-values-from-labels/   |   Difficulty: Medium
#
# Problem Description:
# You are given n item's value and label as two integer arrays values and labels. You are also given two integers numWanted and useLimit.
#
# Your task is to find a subset of items with the maximum sum of their values such that:
#
#
# 	The number of items is at most numWanted.
# 	The number of items with the same label is at most useLimit.
#
#
# Return the maximum sum.
#
# Example:
# Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], numWanted = 3, useLimit = 1
#
# Output: 9
#
# Explanation:
#
# The subset chosen is the first, third, and fifth items with the sum of values 5 + 3 + 1.
#
# Constraints:
# n == values.length == labels.length
# 	1 <= n <= 2 * 104
# 	0 <= values[i], labels[i] <= 2 * 104
# 	1 <= numWanted, useLimit <= n
#
# Helpful references (internal KB):
# - Mergesort (array, merge-sort, recursion)
#   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
#   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
#   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
#   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
#   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
# - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
#   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
#   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
#   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
#   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
#   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def largestValsFromLabels(self, values, labels, numWanted, useLimit):
        """
        :type values: List[int]
        :type labels: List[int]
        :type numWanted: int
        :type useLimit: int
        :rtype: int
        """
        items = sorted(zip(values, labels), key=lambda x: -x[0])
        label_count = {}
        total_value = 0
        items_used = 0

        for value, label in items:
            if items_used >= numWanted:
                break
            if label_count.get(label, 0) < useLimit:
                total_value += value
                label_count[label] = label_count.get(label, 0) + 1
                items_used += 1

        return total_value