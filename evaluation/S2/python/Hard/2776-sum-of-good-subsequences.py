# Source: https://leetcode.com/problems/sum-of-good-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums. A good subsequence is defined as a subsequence of nums where the absolute difference between any two consecutive elements in the subsequence is exactly 1.
#
# Return the sum of all possible good subsequences of nums.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note that a subsequence of size 1 is considered good by definition.
#
# Example:
# Input: nums = [1,2,1]
#
# Output: 14
#
# Explanation:
#
#
# 	Good subsequences are: [1], [2], [1], [1,2], [2,1], [1,2,1].
# 	The sum of elements in these subsequences is 14.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
#   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
#   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
#   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sumOfGoodSubsequences(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        from collections import Counter
        
        count = Counter(nums)
        result = 0
        
        for num in count:
            freq = count[num]
            result += (pow(2, freq, MOD) - 1) % MOD
            result %= MOD
            
            if num - 1 in count:
                result += (pow(2, freq, MOD) - 1) * (pow(2, count[num - 1], MOD) - 1) % MOD
                result %= MOD
            
            if num + 1 in count:
                result += (pow(2, freq, MOD) - 1) * (pow(2, count[num + 1], MOD) - 1) % MOD
                result %= MOD
        
        return result