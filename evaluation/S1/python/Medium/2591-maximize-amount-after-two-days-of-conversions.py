# Source: https://leetcode.com/problems/maximize-amount-after-two-days-of-conversions/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string initialCurrency, and you start with 1.0 of initialCurrency.
#
# You are also given four arrays with currency pairs (strings) and rates (real numbers):
#
#
# 	pairs1[i] = [startCurrencyi, targetCurrencyi] denotes that you can convert from startCurrencyi to targetCurrencyi at a rate of rates1[i] on day 1.
# 	pairs2[i] = [startCurrencyi, targetCurrencyi] denotes that you can convert from startCurrencyi to targetCurrencyi at a rate of rates2[i] on day 2.
# 	Also, each targetCurrency can be converted back to its corresponding startCurrency at a rate of 1 / rate.
#
#
# You can perform any number of conversions, including zero, using rates1 on day 1, followed by any number of additional conversions, including zero, using rates2 on day 2.
#
# Return the maximum amount of initialCurrency you can have after performing any number of conversions on both days in order.
#
# Note: Conversion rates are valid, and there will be no contradictions in the rates for either day. The rates for the days are independent of each other.
#
# Example:
# Input: initialCurrency = "EUR", pairs1 = [["EUR","USD"],["USD","JPY"]], rates1 = [2.0,3.0], pairs2 = [["JPY","USD"],["USD","CHF"],["CHF","EUR"]], rates2 = [4.0,5.0,6.0]
#
# Output: 720.00000
#
# Explanation:
#
# To get the maximum amount of EUR, starting with 1.0 EUR:
#
#
# 	On Day 1:
# 	
# 		Convert EUR to USD to get 2.0 USD.
# 		Convert USD to JPY to get 6.0 JPY.
# 	
# 	
# 	On Day 2:
# 	
# 		Convert JPY to USD to get 24.0 USD.
# 		Convert USD to CHF to get 120.0 CHF.
# 		Finally, convert CHF to EUR to get 720.0 EUR.
#
# Constraints:
# 1 <= initialCurrency.length <= 3
# 	initialCurrency consists only of uppercase English letters.
# 	1 <= n == pairs1.length <= 10
# 	1 <= m == pairs2.length <= 10
# 	pairs1[i] == [startCurrencyi, targetCurrencyi]
# 	pairs2[i] == [startCurrencyi, targetCurrencyi]
# 	1 <= startCurrencyi.length, targetCurrencyi.length <= 3
# 	startCurrencyi and targetCurrencyi consist only of uppercase English letters.
# 	rates1.length == n
# 	rates2.length == m
# 	1.0 <= rates1[i], rates2[i] <= 10.0
# 	The input is generated such that there are no contradictions or cycles in the conversion graphs for either day.
# 	The input is generated such that the output is at most 5 * 1010.
#
# Helpful references (internal KB):
# - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
#   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
#   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
#   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
#   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
#   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
# - Chinese Remainder Theorem (number, recursion, mod-exp)
#   • When to use: When you need to find a unique integer solution that satisfies a system of linear congruences with pairwise coprime moduli. It is used to reconstruct a number from its remainders modulo several divisors.
#   • Idea: The Chinese Remainder Theorem (CRT) finds a unique solution x modulo the product of several pairwise coprime moduli, given a system of congruences. It typically involves computing modular inverses and combining solutions, with a complexity often dominated by modular exponentiation or extended Euclidean algorithm, usually O(N log M) or O(N log(max_modulus)).
#   • Invariants: The current combined solution 'x' satisfies 'x % m_i == a_i' for all congruences '(a_i, m_i)' processed so far.; The current combined modulus 'M' is the product of all individual moduli processed so far.
#   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
#   • Pitfalls: Forgetting to check if moduli are pairwise coprime.; Incorrectly calculating modular inverses.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxAmount(self, initialCurrency, pairs1, rates1, pairs2, rates2):
        """
        :type initialCurrency: str
        :type pairs1: List[List[str]]
        :type rates1: List[float]
        :type pairs2: List[List[str]]
        :type rates2: List[float]
        :rtype: float
        """
        from collections import defaultdict
        import math

        def build_graph(pairs, rates):
            graph = defaultdict(list)
            for (src, dst), rate in zip(pairs, rates):
                graph[src].append((dst, rate))
                graph[dst].append((src, 1.0 / rate))
            return graph

        def floyd_warshall(graph):
            currencies = list(graph.keys())
            dist = {c1: {c2: 0.0 for c2 in currencies} for c1 in currencies}

            for c in currencies:
                dist[c][c] = 1.0

            for src in graph:
                for dst, rate in graph[src]:
                    dist[src][dst] = max(dist[src][dst], rate)

            for k in currencies:
                for i in currencies:
                    for j in currencies:
                        if dist[i][k] > 0 and dist[k][j] > 0:
                            dist[i][j] = max(dist[i][j], dist[i][k] * dist[k][j])

            return dist

        graph1 = build_graph(pairs1, rates1)
        graph2 = build_graph(pairs2, rates2)

        dist1 = floyd_warshall(graph1)
        dist2 = floyd_warshall(graph2)

        max_amount = 1.0

        for mid_currency in dist1[initialCurrency]:
            if dist1[initialCurrency][mid_currency] > 0:
                amount_after_day1 = dist1[initialCurrency][mid_currency]
                if mid_currency in dist2:
                    amount_after_day2 = dist2[mid_currency].get(initialCurrency, 0.0)
                    if amount_after_day2 > 0:
                        total_amount = amount_after_day1 * amount_after_day2
                        max_amount = max(max_amount, total_amount)

        return max_amount