# Source: https://leetcode.com/problems/sorted-gcd-pair-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums of length n and an integer array queries.
#
# Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
#
# For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
#
# Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
#
# The term gcd(a, b) denotes the greatest common divisor of a and b.
#
# Example:
# Input: nums = [2,3,4], queries = [0,2,2]
#
# Output: [1,2,2]
#
# Explanation:
#
# gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
#
# After sorting in ascending order, gcdPairs = [1, 1, 2].
#
# So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].
#
# Constraints:
# 2 <= n == nums.length <= 105
# 	1 <= nums[i] <= 5 * 104
# 	1 <= queries.length <= 105
# 	0 <= queries[i] < n * (n - 1) / 2
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def gcdValues(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        from math import gcd
        from collections import Counter

        n = len(nums)
        max_num = max(nums)
        freq = Counter(nums)

        # Step 1: Count the frequency of each number in nums
        count = [0] * (max_num + 1)
        for num in nums:
            count[num] += 1

        # Step 2: Calculate the frequency of each GCD value
        gcd_count = [0] * (max_num + 1)
        for i in range(1, max_num + 1):
            for j in range(i, max_num + 1, i):
                gcd_count[i] += count[j]

        # Step 3: Calculate the number of pairs for each GCD value
        pair_count = [0] * (max_num + 1)
        for i in range(1, max_num + 1):
            pair_count[i] = gcd_count[i] * (gcd_count[i] - 1) // 2

        # Step 4: Create a sorted list of GCD values based on their pair counts
        gcd_pairs = []
        for i in range(1, max_num + 1):
            if pair_count[i] > 0:
                gcd_pairs.extend([i] * pair_count[i])
        
        gcd_pairs.sort()

        # Step 5: Answer the queries
        answer = []
        for q in queries:
            answer.append(gcd_pairs[q])

        return answer