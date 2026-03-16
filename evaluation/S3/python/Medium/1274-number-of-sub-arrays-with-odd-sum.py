# Source: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers arr, return the number of subarrays with an odd sum.
#
# Since the answer can be very large, return it modulo 109 + 7.
#
# Example:
# Input: arr = [1,3,5]
# Output: 4
# Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
# All sub-arrays sum are [1,4,9,3,8,5].
# Odd sums are [1,9,3,5] so the answer is 4.
#
# Constraints:
# 1 <= arr.length <= 105
# 	1 <= arr[i] <= 100
#
# Helpful references (internal KB):
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
# - Binary Exponentiation by Factoring (number, counting, mod-exp)
#   • When to use: Use when performing modular exponentiation for an odd base modulo a power of two, especially when dealing with specific logarithmic-like functions or inverses in this modulus.
#   • Idea: This technique computes modular exponentiation for an odd base modulo a power of two by factoring the exponent or its inverse into a product of terms like (2^n+1). It leverages bit manipulation to efficiently find this factorization, allowing for O(d) or O(d log d) complexity where d is the exponent of the modulus.
#   • Invariants: During the iterative process to find $x^{-1} \pmod{2^d}$, the current value of $x$ is always odd.; After processing bit $n$, the $n$-th bit of the current $x$ (for $x^{-1}$ calculation) is zero, and lower bits are unchanged.
#   • Tips: Precompute $4L(2^n+1)$ values for efficiency.; Leverage bitwise operations for multiplying by $2^n+1$ (e.g., x = x + (x << n)).
#   • Pitfalls: This method is specific to odd bases and moduli of the form $2^d$; it's not a general modular exponentiation.; Careful handling of negative results from $4L(x^{-1})$ when working with modular arithmetic.
# - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
#   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
#   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
#   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
#   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
#   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numOfSubarrays(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        odd_count = 0
        even_count = 1  # Start with one even prefix sum (the empty subarray)
        result = 0

        for num in arr:
            if num % 2 == 1:  # If the current number is odd
                odd_count, even_count = even_count, odd_count  # Swap counts
            # Add the number of odd prefix sums to the result
            result = (result + odd_count) % MOD
            # Update the count of even prefix sums
            even_count += 1

        return result