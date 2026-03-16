# Source: https://leetcode.com/problems/h-index-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper and citations is sorted in non-descending order, return the researcher's h-index.
#
# According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value of h such that the given researcher has published at least h papers that have each been cited at least h times.
#
# You must write an algorithm that runs in logarithmic time.
#
# Example:
# Input: citations = [0,1,3,5,6]
# Output: 3
# Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had received 0, 1, 3, 5, 6 citations respectively.
# Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
#
# Constraints:
# n == citations.length
# 	1 <= n <= 105
# 	0 <= citations[i] <= 1000
# 	citations is sorted in ascending order.
#
# Helpful references (internal KB):
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
# - Longest increasing subsequence (array, dp-1d, binary-search)
#   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
#   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
#   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
#   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
#   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
# - Longest Increasing Subsequence (array, dp-1d, binary-search)
#   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order. It is often applied to optimization problems involving ordered subsets.
#   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence where all elements are sorted in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search optimization, or O(N^2) using basic DP.
#   • Invariants: The 'tails' array always stores the smallest ending element for all increasing subsequences of a given length.; The 'tails' array remains sorted in strictly increasing order throughout the algorithm's execution.
#   • Tips: The O(N log N) approach uses a 'tails' array to store the smallest tail of all increasing subsequences of length 'i+1'.; Binary search is crucial for efficiently finding the correct position for the current element in the 'tails' array.
#   • Pitfalls: Confusing subsequence with contiguous subarray or substring.; Incorrectly updating or searching in the 'tails' array, leading to wrong lengths or values.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def hIndex(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        n = len(citations)
        low, high = 0, n

        while low < high:
            mid = (low + high) // 2
            if citations[mid] >= n - mid:
                high = mid
            else:
                low = mid + 1

        return n - low