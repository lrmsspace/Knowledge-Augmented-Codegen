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
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# - Flows with demands (graph, binary-search-answer)
#   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
#   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
#   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
#   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
#   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
# - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
#   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
#   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
#   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
#   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
#   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
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
        possible_costs = set()

        def backtrack(current_cost, index):
            if current_cost > target + 10000:  # Prune search space
                return
            if index == len(toppingCosts):
                possible_costs.add(current_cost)
                return

            # Explore three options for each topping: 0, 1, or 2
            backtrack(current_cost, index + 1)  # No topping
            backtrack(current_cost + toppingCosts[index], index + 1)  # One topping
            backtrack(current_cost + 2 * toppingCosts[index], index + 1)  # Two toppings

        for base in baseCosts:
            backtrack(base, 0)

        closest = None
        for cost in possible_costs:
            if closest is None or abs(cost - target) < abs(closest - target) or (abs(cost - target) == abs(closest - target) and cost < closest):
                closest = cost

        return closest