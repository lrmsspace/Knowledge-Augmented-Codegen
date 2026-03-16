// Source: https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n, representing the number of employees in a company. Each employee is assigned a unique ID from 1 to n, and employee 1 is the CEO. You are given two 1-based integer arrays, present and future, each of length n, where:
//
//
// 	present[i] represents the current price at which the ith employee can buy a stock today.
// 	future[i] represents the expected price at which the ith employee can sell the stock tomorrow.
//
//
// The company's hierarchy is represented by a 2D integer array hierarchy, where hierarchy[i] = [ui, vi] means that employee ui is the direct boss of employee vi.
//
// Additionally, you have an integer budget representing the total funds available for investment.
//
// However, the company has a discount policy: if an employee's direct boss purchases their own stock, then the employee can buy their stock at half the original price (floor(present[v] / 2)).
//
// Return the maximum profit that can be achieved without exceeding the given budget.
//
// Note:
//
//
// 	You may buy each stock at most once.
// 	You cannot use any profit earned from future stock prices to fund additional investments and must buy only from budget.
//
// Example:
// Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3
//
// Output: 5
//
// Explanation:
//
//
//
//
// 	Employee 1 buys the stock at price 1 and earns a profit of 4 - 1 = 3.
// 	Since Employee 1 is the direct boss of Employee 2, Employee 2 gets a discounted price of floor(2 / 2) = 1.
// 	Employee 2 buys the stock at price 1 and earns a profit of 3 - 1 = 2.
// 	The total buying cost is 1 + 1 = 2 <= budget. Thus, the maximum total profit achieved is 3 + 2 = 5.
//
// Constraints:
// 1 <= n <= 160
// 	present.length, future.length == n
// 	1 <= present[i], future[i] <= 50
// 	hierarchy.length == n - 1
// 	hierarchy[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= budget <= 160
// 	There are no duplicate edges.
// 	Employee 1 is the direct or indirect boss of every employee.
// 	The input graph hierarchy is guaranteed to have no cycles.
//

/**
 * @param {number} n
 * @param {number[]} present
 * @param {number[]} future
 * @param {number[][]} hierarchy
 * @param {number} budget
 * @return {number}
 */
var maxProfit = function(n, present, future, hierarchy, budget) {
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v] of hierarchy) {
        graph[u - 1].push(v - 1);
    }
    const dp = new Array(n).fill(0).map(() => new Array(budget + 1).fill(0).map(() => [0, 0]));
    const dfs = (u) => {
        for (const v of graph[u]) {
            dfs(v);
            for (let b = budget; b >= 0; b--) {
                for (let k = 0; k <= b; k++) {
                    dp[u][b][0] = Math.max(dp[u][b][0], dp[u][b - k][0] + Math.max(dp[v][k][0], dp[v][k][1]));
                    dp[u][b][1] = Math.max(dp[u][b][1], dp[u][b - k][1] + dp[v][k][0]);
                }
            }
        }
        for (let b = budget; b >= present[u]; b--) {
            dp[u][b][0] = Math.max(dp[u][b][0], dp[u][b - present[u]][0] + future[u] - present[u]);
        }
        const discountedPrice = Math.floor(present[u] / 2);
        for (let b = budget; b >= discountedPrice; b--) {
            dp[u][b][1] = Math.max(dp[u][b][1], dp[u][b - discountedPrice][1] + future[u] - discountedPrice);
        }
    };
    dfs(0);
    return Math.max(dp[0][budget][0], dp[0][budget][1]);    
};
