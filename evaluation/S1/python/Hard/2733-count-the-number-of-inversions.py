# Source: https://leetcode.com/problems/count-the-number-of-inversions/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti] represents the end index and the inversion count of each requirement.
#
# A pair of indices (i, j) from an integer array nums is called an inversion if:
#
#
# 	i < j and nums[i] > nums[j]
#
#
# Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all requirements[i], perm[0..endi] has exactly cnti inversions.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: n = 3, requirements = [[2,2],[0,0]]
#
# Output: 2
#
# Explanation:
#
# The two permutations are:
#
#
# 	[2, 0, 1]
#
# 	
# 		Prefix [2, 0, 1] has inversions (0, 1) and (0, 2).
# 		Prefix [2] has 0 inversions.
# 	
# 	
# 	[1, 2, 0]
# 	
# 		Prefix [1, 2, 0] has inversions (0, 2) and (1, 2).
# 		Prefix [1] has 0 inversions.
#
# Constraints:
# 2 <= n <= 300
# 	1 <= requirements.length <= n
# 	requirements[i] = [endi, cnti]
# 	0 <= endi <= n - 1
# 	0 <= cnti <= 400
# 	The input is generated such that there is at least one i such that endi == n - 1.
# 	The input is generated such that all endi are unique.
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
#   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
#   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
#   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
#   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
#   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
# - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
#   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
#   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
#   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
#   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfPermutations(self, n, requirements):
        """
        :type n: int
        :type requirements: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        requirements.sort()  # Sort by end index

        # dp[i][j] = number of permutations of [0..i] with j inversions
        dp = [[0] * (n * (n - 1) // 2 + 1) for _ in range(n + 1)]
        dp[0][0] = 1

        for i in range(1, n + 1):
            for j in range(i * (i - 1) // 2 + 1):
                for k in range(min(j, i - 1) + 1):
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % MOD

        result = 0
        for end, cnt in requirements:
            if cnt <= end * (end - 1) // 2:
                result = (result + dp[end + 1][cnt]) % MOD

        return result