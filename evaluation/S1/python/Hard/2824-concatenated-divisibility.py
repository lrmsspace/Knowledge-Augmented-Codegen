# Source: https://leetcode.com/problems/concatenated-divisibility/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of positive integers nums and a positive integer k.
#
# A permutation of nums is said to form a divisible concatenation if, when you concatenate the decimal representations of the numbers in the order specified by the permutation, the resulting number is divisible by k.
#
# Return the lexicographically smallest permutation (when considered as a list of integers) that forms a divisible concatenation. If no such permutation exists, return an empty list.
#
# Example:
# Input: nums = [3,12,45], k = 5
#
# Output: [3,12,45]
#
# Explanation:
#
#
# 	
# 		
# 			Permutation
# 			Concatenated Value
# 			Divisible by 5
# 		
# 	
# 	
# 		
# 			[3, 12, 45]
# 			31245
# 			Yes
# 		
# 		
# 			[3, 45, 12]
# 			34512
# 			No
# 		
# 		
# 			[12, 3, 45]
# 			12345
# 			Yes
# 		
# 		
# 			[12, 45, 3]
# 			12453
# 			No
# 		
# 		
# 			[45, 3, 12]
# 			45312
# 			No
# 		
# 		
# 			[45, 12, 3]
# 			45123
# 			No
# 		
# 	
#
#
# The lexicographically smallest permutation that forms a divisible concatenation is [3,12,45].
#
# Constraints:
# 1 <= nums.length <= 13
# 	1 <= nums[i] <= 105
# 	1 <= k <= 100
#
# Helpful references (internal KB):
# - Generating all K-combinations (bitset, recursion, enumeration)
#   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
#   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
#   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
#   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
#   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
# - palindrome-partitioning (string, array, backtracking, recursion)
#   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
#   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
#   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
#   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
#   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
# - Binomial Coefficients (array, number, mod-exp, enumeration)
#   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
#   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
#   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
#   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
#   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def concatenatedDivisibility(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        from itertools import permutations

        # Generate all permutations of nums
        for perm in sorted(permutations(nums)):
            # Concatenate the numbers in the current permutation
            concatenated_number = int(''.join(map(str, perm)))
            # Check if the concatenated number is divisible by k
            if concatenated_number % k == 0:
                return list(perm)

        return []  # Return an empty list if no valid permutation is found