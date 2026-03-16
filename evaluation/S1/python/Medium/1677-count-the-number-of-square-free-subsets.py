# Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer 0-indexed array nums.
#
# A subset of the array nums is square-free if the product of its elements is a square-free integer.
#
# A square-free integer is an integer that is divisible by no square number other than 1.
#
# Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
#
# A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
#
# Example:
# Input: nums = [3,4,4,5]
# Output: 3
# Explanation: There are 3 square-free subsets in this example:
# - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
# - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
# - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
# It can be proven that there are no more than 3 square-free subsets in the given array.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 30
#
# Helpful references (internal KB):
# - Sieve of Eratosthenes (array, sieve, enumeration)
#   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
#   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
#   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
#   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def squareFreeSubsets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        primes = [2,3,5,7,11,13,17,19,23,29]
        prime_count = len(primes)
        
        # Precompute the bitmask for each number from 1 to 30
        num_mask = [0] * 31
        for num in range(1, 31):
            mask = 0
            is_square_free = True
            for i, prime in enumerate(primes):
                count = 0
                temp = num
                while temp % prime == 0:
                    temp //= prime
                    count += 1
                if count > 1:
                    is_square_free = False
                    break
                elif count == 1:
                    mask |= (1 << i)
            if is_square_free:
                num_mask[num] = mask
        
        # Count occurrences of each number in nums
        count = [0] * 31
        for num in nums:
            count[num] += 1
        
        # DP array to count subsets
        dp = [0] * (1 << prime_count)
        dp[0] = 1  # Empty subset
        
        for num in range(1, 31):
            if count[num] == 0 or num_mask[num] == 0:
                continue
            
            curr_mask = num_mask[num]
            for mask in range((1 << prime_count) - 1, -1, -1):
                if (mask & curr_mask) == 0:  # No common prime factors
                    dp[mask | curr_mask] = (dp[mask | curr_mask] + dp[mask] * count[num]) % MOD
        
        # Sum all non-empty subsets
        result = sum(dp) - dp[0]
        return result % MOD