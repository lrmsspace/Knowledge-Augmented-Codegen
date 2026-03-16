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

        tree = defaultdict(list)
        for u, v in hierarchy:
            tree[u - 1].append(v - 1)

        dp = [ [0] * (budget + 1) for _ in range(n) ]

        def dfs(u):
            for v in tree[u]:
                dfs(v)

            for b in range(budget + 1):
                dp[u][b] = 0

            for v in tree[u]:
                new_dp = [0] * (budget + 1)
                for b in range(budget + 1):
                    for k in range(b + 1):
                        new_dp[b] = max(new_dp[b], dp[u][b - k] + dp[v][k])
                dp[u] = new_dp

            for b in range(budget, present[u] - 1, -1):
                dp[u][b] = max(dp[u][b], dp[u][b - present[u]] + future[u] - present[u])

            discounted_price = present[u] // 2
            for b in range(budget, discounted_price - 1, -1):
                dp[u][b] = max(dp[u][b], dp[u][b - discounted_price] + future[u] - discounted_price)

        dfs(0)
        return dp[0][budget]