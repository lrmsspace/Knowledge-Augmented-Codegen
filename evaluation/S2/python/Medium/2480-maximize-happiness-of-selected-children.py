# Source: https://leetcode.com/problems/maximize-happiness-of-selected-children/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array happiness of length n, and a positive integer k.
#
# There are n children standing in a queue, where the ith child has happiness value happiness[i]. You want to select k children from these n children in k turns.
#
# In each turn, when you select a child, the happiness value of all the children that have not been selected till now decreases by 1. Note that the happiness value cannot become negative and gets decremented only if it is positive.
#
# Return the maximum sum of the happiness values of the selected children you can achieve by selecting k children.
#
# Example:
# Input: happiness = [1,2,3], k = 2
# Output: 4
# Explanation: We can pick 2 children in the following way:
# - Pick the child with the happiness value == 3. The happiness value of the remaining children becomes [0,1].
# - Pick the child with the happiness value == 1. The happiness value of the remaining child becomes [0]. Note that the happiness value cannot become less than 0.
# The sum of the happiness values of the selected children is 3 + 1 = 4.
#
# Constraints:
# 1 <= n == happiness.length <= 2 * 105
# 	1 <= happiness[i] <= 108
# 	1 <= k <= n
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
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
    def maximumHappinessSum(self, happiness, k):
        """
        :type happiness: List[int]
        :type k: int
        :rtype: int
        """
        # Sort the happiness values in descending order
        happiness.sort(reverse=True)

        total_happiness = 0
        for i in range(k):
            # Add the happiness value of the selected child
            total_happiness += happiness[i]
            # Decrease the happiness of remaining children by 1 (if positive)
            for j in range(i + 1, len(happiness)):
                if happiness[j] > 0:
                    happiness[j] -= 1

        return total_happiness