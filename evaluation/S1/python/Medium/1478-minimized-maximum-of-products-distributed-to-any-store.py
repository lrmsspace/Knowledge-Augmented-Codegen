# Source: https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n indicating there are n specialty retail stores. There are m product types of varying amounts, which are given as a 0-indexed integer array quantities, where quantities[i] represents the number of products of the ith product type.
#
# You need to distribute all products to the retail stores following these rules:
#
#
# 	A store can only be given at most one product type but can be given any amount of it.
# 	After distribution, each store will have been given some number of products (possibly 0). Let x represent the maximum number of products given to any store. You want x to be as small as possible, i.e., you want to minimize the maximum number of products that are given to any store.
#
#
# Return the minimum possible x.
#
# Example:
# Input: n = 6, quantities = [11,6]
# Output: 3
# Explanation: One optimal way is:
# - The 11 products of type 0 are distributed to the first four stores in these amounts: 2, 3, 3, 3
# - The 6 products of type 1 are distributed to the other two stores in these amounts: 3, 3
# The maximum number of products given to any store is max(2, 3, 3, 3, 3, 3) = 3.
#
# Constraints:
# m == quantities.length
# 	1 <= m <= n <= 105
# 	1 <= quantities[i] <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Flows with demands (graph, binary-search-answer)
#   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
#   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
#   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
#   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
#   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
# - Linear Diophantine Equation (number, greedy)
#   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
#   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
#   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
#   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
#   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimizedMaximum(self, n, quantities):
        """
        :type n: int
        :type quantities: List[int]
        :rtype: int
        """
        def canDistribute(maxProducts):
            storesNeeded = 0
            for qty in quantities:
                storesNeeded += (qty + maxProducts - 1) // maxProducts
            return storesNeeded <= n

        left, right = 1, max(quantities)
        answer = right

        while left <= right:
            mid = (left + right) // 2
            if canDistribute(mid):
                answer = mid
                right = mid - 1
            else:
                left = mid + 1

        return answer