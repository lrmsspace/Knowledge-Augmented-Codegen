# Source: https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array nums of non-negative integers, and two integers l and r.
#
# Return the count of sub-multisets within nums where the sum of elements in each subset falls within the inclusive range of [l, r].
#
# Since the answer may be large, return it modulo 109 + 7.
#
# A sub-multiset is an unordered collection of elements of the array in which a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the number of occurrences of x in the array.
#
# Note that:
#
#
# 	Two sub-multisets are the same if sorting both sub-multisets results in identical multisets.
# 	The sum of an empty multiset is 0.
#
# Example:
# Input: nums = [1,2,2,3], l = 6, r = 6
# Output: 1
# Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	0 <= nums[i] <= 2 * 104
# 	Sum of nums does not exceed 2 * 104.
# 	0 <= l <= r <= 2 * 104
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
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
#   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
#   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
#   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
#   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countSubMultisets(self, nums, l, r):
        """
        :type nums: List[int]
        :type l: int
        :type r: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        # Step 1: Count occurrences of each unique number
        from collections import Counter
        count = Counter(nums)
        
        # Step 2: Create a list of (number, frequency) pairs
        unique_nums = list(count.items())
        
        # Step 3: Initialize DP array for counting subsets with sums up to r
        dp = [0] * (r + 1)
        dp[0] = 1  # There's one way to have a sum of 0: the empty set
        
        # Step 4: Fill the DP array using the counts of each unique number
        for num, freq in unique_nums:
            # We need to consider using this number from 0 to freq times
            for j in range(r, -1, -1):
                for k in range(1, freq + 1):
                    if j >= k * num:
                        dp[j] = (dp[j] + dp[j - k * num]) % MOD
                    else:
                        break
        
        # Step 5: Calculate the result by summing counts for sums in [l, r]
        result = sum(dp[l:r + 1]) % MOD
        
        return result