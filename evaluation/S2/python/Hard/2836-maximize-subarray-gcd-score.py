# Source: https://leetcode.com/problems/maximize-subarray-gcd-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of positive integers nums and an integer k.
#
# You may perform at most k operations. In each operation, you can choose one element in the array and double its value. Each element can be doubled at most once.
#
# The score of a contiguous subarray is defined as the product of its length and the greatest common divisor (GCD) of all its elements.
#
# Your task is to return the maximum score that can be achieved by selecting a contiguous subarray from the modified array.
#
# Note:
#
#
#  The greatest common divisor (GCD) of an array is the largest integer that evenly divides all the array elements.
#
# Example:
# Input: nums = [2,4], k = 1
#
# Output: 8
#
# Explanation:
#
#
#  Double nums[0] to 4 using one operation. The modified array becomes [4, 4].
#  The GCD of the subarray [4, 4] is 4, and the length is 2.
#  Thus, the maximum possible score is 2 × 4 = 8.
#
# Constraints:
# 1 <= n == nums.length <= 1500
#  1 <= nums[i] <= 109
#  1 <= k <= n
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
#   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
#   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
#   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
#   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
#   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
# - Generating all K-combinations (bitset, enumeration)
#   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
#   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
#   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
#   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
#   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
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
    def maxGCDScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        # Step 1: Generate all combinations of indices for doubling
        from math import gcd
        from itertools import combinations
        
        n = len(nums)
        max_score = 0
        
        # Check all combinations of indices to double (up to k)
        for num_doubles in range(k + 1):
            for indices in combinations(range(n), num_doubles):
                modified_nums = nums[:]
                for idx in indices:
                    modified_nums[idx] *= 2
                
                # Step 2: Calculate GCD for all subarrays and update max score
                for start in range(n):
                    current_gcd = 0
                    for end in range(start, n):
                        current_gcd = gcd(current_gcd, modified_nums[end])
                        score = (end - start + 1) * current_gcd
                        max_score = max(max_score, score)
        
        return max_score