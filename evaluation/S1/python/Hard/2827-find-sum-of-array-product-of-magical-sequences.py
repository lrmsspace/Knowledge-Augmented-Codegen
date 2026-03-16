# Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integers, m and k, and an integer array nums.
# A sequence of integers seq is called magical if:
#
#
# 	seq has a size of m.
# 	0 <= seq[i] < nums.length
# 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
#
#
# The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
#
# Return the sum of the array products for all valid magical sequences.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# A set bit refers to a bit in the binary representation of a number that has a value of 1.
#
# Example:
# Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
#
# Output: 991600007
#
# Explanation:
#
# All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
#
# Constraints:
# 1 <= k <= m <= 30
# 	1 <= nums.length <= 50
# 	1 <= nums[i] <= 108
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
#   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
#   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
#   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
#   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
#   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
# - Operations on polynomials and series (array, recursion)
#   • When to use: Use when counting combinations or permutations with specific sum constraints, or when analyzing discrete probability distributions through polynomial multiplication.
#   • Idea: This technique represents combinatorial problems as coefficients of polynomials or formal power series. Solutions involve operations like polynomial multiplication and exponentiation, often with a time complexity dependent on the degree of the polynomials.
#   • Invariants: The degree of the product polynomial is the sum of the degrees of the input polynomials.; The coefficient of x^k in the product is the sum of A[i]*B[j] for all i+j=k.
#   • Tips: Represent individual choices as polynomial terms.; Multiply polynomials to combine independent events.
#   • Pitfalls: Incorrectly forming the initial generating function.; Naive polynomial multiplication can be computationally expensive.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def magicalSum(self, m, k, nums):
        """
        :type m: int
        :type k: int
        :type nums: List[int]
        :rtype: int
        """
        # Step 1: Precompute the count of magical sequences for each possible sum of powers of 2
        from collections import Counter
        mod = 10**9 + 7
        
        # Count how many ways to choose m indices that sum to a certain value
        count = Counter()
        def backtrack(start, path):
            if len(path) == m:
                count[sum(2**i for i in path)] += 1
                return
            for i in range(len(nums)):
                path.append(i)
                backtrack(i, path)
                path.pop()
        
        backtrack(0, [])
        
        # Step 2: Calculate the sum of products for magical sequences with k set bits
        result = 0
        for s, c in count.items():
            if bin(s).count('1') == k:
                product = 1
                for i in range(m):
                    product = (product * nums[i]) % mod
                result = (result + c * product) % mod
        
        return result