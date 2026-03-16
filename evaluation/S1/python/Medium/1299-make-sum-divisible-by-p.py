# Source: https://leetcode.com/problems/make-sum-divisible-by-p/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
#
# Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
#
# A subarray is defined as a contiguous block of elements in the array.
#
# Example:
# Input: nums = [3,1,4,2], p = 6
# Output: 1
# Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	1 <= p <= 109
#
# Helpful references (internal KB):
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - String Hashing (string, number, hashing)
#   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
#   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
#   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
#   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
#   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minSubarray(self, nums, p):
        """
        :type nums: List[int]
        :type p: int
        :rtype: int
        """
        total_mod = sum(nums) % p
        if total_mod == 0:
            return 0
        
        prefix_mod_index = {0: -1}
        current_mod = 0
        min_length = len(nums)
        
        for i, num in enumerate(nums):
            current_mod = (current_mod + num) % p
            target_mod = (current_mod - total_mod + p) % p
            
            if target_mod in prefix_mod_index:
                min_length = min(min_length, i - prefix_mod_index[target_mod])
            
            prefix_mod_index[current_mod] = i
        
        return min_length if min_length < len(nums) else -1