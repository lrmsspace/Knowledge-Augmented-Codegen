# Source: https://leetcode.com/problems/closest-dessert-cost/   |   Difficulty: Medium
#
# Problem Description:
# You would like to make dessert and are preparing to buy the ingredients. You have n ice cream base flavors and m types of toppings to choose from. You must follow these rules when making your dessert:
#
#
# 	There must be exactly one ice cream base.
# 	You can add one or more types of topping or have no toppings at all.
# 	There are at most two of each type of topping.
#
#
# You are given three inputs:
#
#
# 	baseCosts, an integer array of length n, where each baseCosts[i] represents the price of the ith ice cream base flavor.
# 	toppingCosts, an integer array of length m, where each toppingCosts[i] is the price of one of the ith topping.
# 	target, an integer representing your target price for dessert.
#
#
# You want to make a dessert with a total cost as close to target as possible.
#
# Return the closest possible cost of the dessert to target. If there are multiple, return the lower one.
#
# Example:
# Input: baseCosts = [1,7], toppingCosts = [3,4], target = 10
# Output: 10
# Explanation: Consider the following combination (all 0-indexed):
# - Choose base 1: cost 7
# - Take 1 of topping 0: cost 1 x 3 = 3
# - Take 0 of topping 1: cost 0 x 4 = 0
# Total: 7 + 3 + 0 = 10.
#
# Constraints:
# n == baseCosts.length
# 	m == toppingCosts.length
# 	1 <= n, m <= 10
# 	1 <= baseCosts[i], toppingCosts[i] <= 104
# 	1 <= target <= 104
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def closestCost(self, baseCosts, toppingCosts, target):
        """
        :type baseCosts: List[int]
        :type toppingCosts: List[int]
        :type target: int
        :rtype: int
        """
        closest = float('inf')

        def dfs(cost, index):
            nonlocal closest
            if abs(cost - target) < abs(closest - target) or (abs(cost - target) == abs(closest - target) and cost < closest):
                closest = cost
            if index == len(toppingCosts):
                return
            # Try adding 0, 1, or 2 of the current topping
            for i in range(3):
                dfs(cost + i * toppingCosts[index], index + 1)

        for base in baseCosts:
            dfs(base, 0)

        return closest