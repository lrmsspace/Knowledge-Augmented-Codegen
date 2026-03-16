# Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer eventTime denoting the duration of an event, where the event occurs from time t = 0 to time t = eventTime.
#
# You are also given two integer arrays startTime and endTime, each of length n. These represent the start and end time of n non-overlapping meetings, where the ith meeting occurs during the time [startTime[i], endTime[i]].
#
# You can reschedule at most k meetings by moving their start time while maintaining the same duration, to maximize the longest continuous period of free time during the event.
#
# The relative order of all the meetings should stay the same and they should remain non-overlapping.
#
# Return the maximum amount of free time possible after rearranging the meetings.
#
# Note that the meetings can not be rescheduled to a time outside the event.
#
# Example:
# Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
#
# Output: 2
#
# Explanation:
#
#
#
# Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the time [0, 2].
#
# Constraints:
# 1 <= eventTime <= 109
# 	n == startTime.length == endTime.length
# 	2 <= n <= 105
# 	1 <= k <= n
# 	0 <= startTime[i] < endTime[i] <= eventTime
# 	endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Longest increasing subsequence (array, dp-1d, binary-search)
#   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
#   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
#   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
#   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
#   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxFreeTime(self, eventTime, k, startTime, endTime):
        """
        :type eventTime: int
        :type k: int
        :type startTime: List[int]
        :type endTime: List[int]
        :rtype: int
        """
        n = len(startTime)
        gaps = [startTime[0]] + [startTime[i] - endTime[i - 1] for i in range(1, n)] + [eventTime - endTime[-1]]
        prefix_sum = [0] * (n + 2)
        for i in range(1, n + 2):
            prefix_sum[i] = prefix_sum[i - 1] + gaps[i - 1]

        max_free_time = 0
        for i in range(n - k + 1):
            free_time = prefix_sum[i + k + 1] - prefix_sum[i]
            max_free_time = max(max_free_time, free_time)

        return max_free_time