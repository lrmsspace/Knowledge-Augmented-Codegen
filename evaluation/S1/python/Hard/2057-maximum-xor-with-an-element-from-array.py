# Source: https://leetcode.com/problems/maximum-xor-with-an-element-from-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].
#
# The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.
#
# Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.
#
# Example:
# Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
# Output: [3,3,7]
# Explanation:
# 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
# 2) 1 XOR 2 = 3.
# 3) 5 XOR 2 = 7.
#
# Constraints:
# 1 <= nums.length, queries.length <= 105
# 	queries[i].length == 2
# 	0 <= nums[j], xi, mi <= 109
#
# Helpful references (internal KB):
# - Mergesort (array, merge-sort)
#   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
#   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
#   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
#   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
#   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
# - Range Minimum Query (array, ds, divide-and-conquer)
#   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
#   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
#   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
#   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
#   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
# - Tries (trie, tree, trie-match)
#   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
#   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
#   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximizeXor(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Step 1: Sort nums and queries
        nums.sort()
        sorted_queries = sorted(enumerate(queries), key=lambda x: x[1][1])  # Sort by mi

        # Step 2: Initialize a Trie for XOR operations
        class TrieNode:
            def __init__(self):
                self.children = {}
        
        class Trie:
            def __init__(self):
                self.root = TrieNode()
            
            def insert(self, num):
                node = self.root
                for i in range(31, -1, -1):
                    bit = (num >> i) & 1
                    if bit not in node.children:
                        node.children[bit] = TrieNode()
                    node = node.children[bit]
            
            def find_max_xor(self, num):
                node = self.root
                max_xor = 0
                for i in range(31, -1, -1):
                    bit = (num >> i) & 1
                    toggled_bit = 1 - bit
                    if toggled_bit in node.children:
                        max_xor |= (1 << i)
                        node = node.children[toggled_bit]
                    else:
                        node = node.children.get(bit, node)
                return max_xor
        
        trie = Trie()
        result = [-1] * len(queries)
        idx = 0
        
        # Step 3: Process each query
        for original_idx, (x, m) in sorted_queries:
            while idx < len(nums) and nums[idx] <= m:
                trie.insert(nums[idx])
                idx += 1
            
            if idx > 0:  # If there are numbers less than or equal to m
                result[original_idx] = trie.find_max_xor(x)
        
        return result