# Source: https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary array nums and an integer k.
#
# A k-bit flip is choosing a subarray of length k from nums and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
#
# Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is not possible, return -1.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [0,1,0], k = 1
# Output: 2
# Explanation: Flip nums[0], then flip nums[2].
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= k <= nums.length
#
# Helpful references (internal KB):
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
#   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
#   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
#   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minKBitFlips(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        flip = [0] * (n + 1)  # flip[i] indicates if we flip at index i
        current_flips = 0
        flips_count = 0

        for i in range(n):
            current_flips ^= flip[i]  # Update current flips based on previous flips
            if nums[i] ^ current_flips == 0:  # If the bit is 0 after flips, we need to flip
                if i + k > n:  # If flipping goes out of bounds, return -1
                    return -1
                flips_count += 1
                current_flips ^= 1  # Flip the current bit
                flip[i + k] ^= 1  # Mark the end of the flip effect

        return flips_count