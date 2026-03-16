# Source: https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n, representing the number of employees in a company. Each employee is assigned a unique ID from 1 to n, and employee 1 is the CEO. You are given two 1-based integer arrays, present and future, each of length n, where:
#
#
# 	present[i] represents the current price at which the ith employee can buy a stock today.
# 	future[i] represents the expected price at which the ith employee can sell the stock tomorrow.
#
#
# The company's hierarchy is represented by a 2D integer array hierarchy, where hierarchy[i] = [ui, vi] means that employee ui is the direct boss of employee vi.
#
# Additionally, you have an integer budget representing the total funds available for investment.
#
# However, the company has a discount policy: if an employee's direct boss purchases their own stock, then the employee can buy their stock at half the original price (floor(present[v] / 2)).
#
# Return the maximum profit that can be achieved without exceeding the given budget.
#
# Note:
#
#
# 	You may buy each stock at most once.
# 	You cannot use any profit earned from future stock prices to fund additional investments and must buy only from budget.
#
# Example:
# Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3
#
# Output: 5
#
# Explanation:
#
#
#
#
# 	Employee 1 buys the stock at price 1 and earns a profit of 4 - 1 = 3.
# 	Since Employee 1 is the direct boss of Employee 2, Employee 2 gets a discounted price of floor(2 / 2) = 1.
# 	Employee 2 buys the stock at price 1 and earns a profit of 3 - 1 = 2.
# 	The total buying cost is 1 + 1 = 2 <= budget. Thus, the maximum total profit achieved is 3 + 2 = 5.
#
# Constraints:
# 1 <= n <= 160
# 	present.length, future.length == n
# 	1 <= present[i], future[i] <= 50
# 	hierarchy.length == n - 1
# 	hierarchy[i] == [ui, vi]
# 	1 <= ui, vi <= n
# 	ui != vi
# 	1 <= budget <= 160
# 	There are no duplicate edges.
# 	Employee 1 is the direct or indirect boss of every employee.
# 	The input graph hierarchy is guaranteed to have no cycles.
#
# Helpful references (internal KB):
# - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
#   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
#   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
#   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
#   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
#   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
# - Search for connected components in a graph (stack, graph, dfs, recursion)
#   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
#   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
#   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
#   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
#   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxProfit(self, n, present, future, hierarchy, budget):
        """
        :type n: int
        :type present: List[int]
        :type future: List[int]
        :type hierarchy: List[List[int]]
        :type budget: int
        :rtype: int
        """
        from collections import defaultdict

        # Build the adjacency list for the hierarchy
        graph = defaultdict(list)
        for u, v in hierarchy:
            graph[u].append(v)

        # Step 1: Find connected components (subtrees) in the hierarchy
        visited = [False] * (n + 1)
        components = []

        def dfs(node, component):
            visited[node] = True
            component.append(node)
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    dfs(neighbor, component)

        for i in range(1, n + 1):
            if not visited[i]:
                component = []
                dfs(i, component)
                components.append(component)

        # Step 2: Calculate profit and cost for each component
        profits_costs = []
        for component in components:
            total_profit = sum(future[i - 1] - present[i - 1] for i in component)
            total_cost = sum(present[i - 1] // 2 if any(j in graph[i] for j in component) else present[i - 1] for i in component)
            profits_costs.append((total_profit, total_cost))

        # Step 3: Knapsack to maximize profit within budget
        dp = [0] * (budget + 1)
        for profit, cost in profits_costs:
            if cost <= budget:
                for b in range(budget, cost - 1, -1):
                    dp[b] = max(dp[b], dp[b - cost] + profit)

        return dp[budget]