# Source: https://leetcode.com/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and two integers, k and limit. Your task is to find a non-empty subsequence of nums that:
#
#
# 	Has an alternating sum equal to k.
# 	Maximizes the product of all its numbers without the product exceeding limit.
#
#
# Return the product of the numbers in such a subsequence. If no subsequence satisfies the requirements, return -1.
#
# The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the sum of the elements at odd indices.
#
# Example:
# Input: nums = [1,2,3], k = 2, limit = 10
#
# Output: 6
#
# Explanation:
#
# The subsequences with an alternating sum of 2 are:
#
#
# 	[1, 2, 3]
#
# 	
# 		Alternating Sum: 1 - 2 + 3 = 2
# 		Product: 1 * 2 * 3 = 6
# 	
# 	
# 	[2]
# 	
# 		Alternating Sum: 2
# 		Product: 2
# 	
# 	
#
#
# The maximum product within the limit is 6.
#
# Constraints:
# 1 <= nums.length <= 150
# 	0 <= nums[i] <= 12
# 	-105 <= k <= 105
# 	1 <= limit <= 5000
#
# Helpful references (internal KB):
# - Longest Increasing Subsequence (array, dp-1d)
#   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
#   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
#   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
#   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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
    def maxProduct(self, nums, k, limit):
        """
        :type nums: List[int]
        :type k: int
        :type limit: int
        :rtype: int
        """
        # Step 1: Generate all subsequences and calculate their alternating sums and products
        from itertools import combinations
        
        max_product = -1
        n = len(nums)
        
        for length in range(1, n + 1):
            for subseq in combinations(nums, length):
                alt_sum = sum(subseq[i] if i % 2 == 0 else -subseq[i] for i in range(len(subseq)))
                product = 1
                for num in subseq:
                    product *= num
                
                # Step 2: Check if the alternating sum equals k and product is within limit
                if alt_sum == k and product <= limit:
                    max_product = max(max_product, product)
        
        return max_product