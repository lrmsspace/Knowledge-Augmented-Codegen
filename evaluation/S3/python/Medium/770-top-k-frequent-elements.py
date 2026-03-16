# Source: https://leetcode.com/problems/top-k-frequent-elements/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
#
# Example:
# Input: nums = [1,1,1,2,2,3], k = 2
#
# Output: [1,2]
#
# Constraints:
# 1 <= nums.length <= 105
# 	-104 <= nums[i] <= 104
# 	k is in the range [1, the number of unique elements in the array].
# 	It is guaranteed that the answer is unique.
#
#
#  
# Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
#
# Helpful references (internal KB):
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - MEX (minimal excluded) of a sequence (ds, enumeration)
#   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
#   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
#   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
#   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
#   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
# - bucket-sort (array, bucket-sort)
#   • When to use: When the input elements are uniformly distributed across a specific range, allowing for efficient partitioning and sorting.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket, then concatenates them. It achieves O(N+K) average time complexity, where N is elements and K is buckets, assuming uniform distribution.
#   • Invariants: All elements from the input are initially present in the unsorted collection.; After distribution, each element resides in exactly one bucket, corresponding to its value range.
#   • Tips: Choose the number of buckets carefully based on data range and distribution.; Use an efficient sorting algorithm for individual buckets (e.g., insertion sort for small buckets).
#   • Pitfalls: Poor performance with non-uniform data distribution, leading to elements clustering in few buckets.; Requires knowing the range of input values beforehand to define bucket boundaries.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def topKFrequent(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        from collections import Counter
        count = Counter(nums)
        freq = [[] for i in range(len(nums) + 1)]
        for num, c in count.items():
            freq[c].append(num)
        
        res = []
        for i in range(len(freq) - 1, 0, -1):
            for num in freq[i]:
                res.append(num)
                if len(res) == k:
                    return res