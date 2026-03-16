# Source: https://leetcode.com/problems/apply-operations-on-array-to-maximize-sum-of-squares/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums and a positive integer k.
#
# You can do the following operation on the array any number of times:
#
#
# 	Choose any two distinct indices i and j and simultaneously update the values of nums[i] to (nums[i] AND nums[j]) and nums[j] to (nums[i] OR nums[j]). Here, OR denotes the bitwise OR operation, and AND denotes the bitwise AND operation.
#
#
# You have to choose k elements from the final array and calculate the sum of their squares.
#
# Return the maximum sum of squares you can achieve.
#
# Since the answer can be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [2,6,5,8], k = 2
# Output: 261
# Explanation: We can do the following operations on the array:
# - Choose i = 0 and j = 3, then change nums[0] to (2 AND 8) = 0 and nums[3] to (2 OR 8) = 10. The resulting array is nums = [0,6,5,10].
# - Choose i = 2 and j = 3, then change nums[2] to (5 AND 10) = 0 and nums[3] to (5 OR 10) = 15. The resulting array is nums = [0,6,0,15].
# We can choose the elements 15 and 6 from the final array. The sum of squares is 152 + 62 = 261.
# It can be shown that this is the maximum value we can get.
#
# Constraints:
# 1 <= k <= nums.length <= 105
# 	1 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
#   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
#   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
#   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
# - Binomial Coefficients (array, number, dp-1d, mod-exp)
#   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
#   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
#   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
#   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
#   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
# - Generating all K-combinations (bitset, recursion, enumeration)
#   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
#   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
#   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
#   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
#   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxSum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        mod = 10**9 + 7
        n = len(nums)
        
        # Step 1: Calculate the sum of squares of the original array
        sum_of_squares = sum(x * x for x in nums) % mod
        
        # Step 2: Calculate the total sum of the array
        total_sum = sum(nums) % mod
        
        # Step 3: The maximum sum of squares after operations can be derived from the total sum
        # The optimal strategy is to combine all elements into one element (the total sum) and then choose it k times.
        max_sum_of_squares = (total_sum * total_sum) % mod
        
        return max_sum_of_squares