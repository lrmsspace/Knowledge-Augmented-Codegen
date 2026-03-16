# Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subsequences of nums with at most k elements.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3], k = 2
#
# Output: 24
#
# Explanation:
#
# The subsequences of nums with at most 2 elements are:
#
#
# 	
# 		
# 			Subsequence 
# 			Minimum
# 			Maximum
# 			Sum
# 		
# 		
# 			[1]
# 			1
# 			1
# 			2
# 		
# 		
# 			[2]
# 			2
# 			2
# 			4
# 		
# 		
# 			[3]
# 			3
# 			3
# 			6
# 		
# 		
# 			[1, 2]
# 			1
# 			2
# 			3
# 		
# 		
# 			[1, 3]
# 			1
# 			3
# 			4
# 		
# 		
# 			[2, 3]
# 			2
# 			3
# 			5
# 		
# 		
# 			Final Total
# 			 
# 			 
# 			24
# 		
# 	
#
#
# The output would be 24.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
# 	1 <= k <= min(70, nums.length)
#
# Helpful references (internal KB):
# - Mergesort (array, merge-sort)
#   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
#   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
#   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
#   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
#   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
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
    def minMaxSums(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        nums.sort()
        
        # Precompute powers of 2 up to n
        pow2 = [1] * (n + 1)
        for i in range(1, n + 1):
            pow2[i] = (pow2[i - 1] * 2) % MOD
        
        total_sum = 0
        
        # Calculate contribution as minimum
        for i in range(n):
            max_size = min(k - 1, n - i - 1)
            if max_size >= 0:
                total_sum = (total_sum + nums[i] * pow2[max_size]) % MOD
        
        # Calculate contribution as maximum
        for i in range(n):
            max_size = min(k - 1, i)
            if max_size >= 0:
                total_sum = (total_sum + nums[i] * pow2[max_size]) % MOD
        
        return total_sum % MOD