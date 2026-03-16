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

class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<vector<int>> tree(n + 1);
        for (const auto& edge : hierarchy) {
            tree[edge[0]].push_back(edge[1]);
        }
        
        // dp[node][cost] = max profit at node with given cost
        vector<vector<int>> dp(n + 1, vector<int>(budget + 1, 0));
        
        function<void(int)> dfs = [&](int node) {
            for (int child : tree[node]) {
                dfs(child);
                
                // Merge dp tables
                for (int c = budget; c >= 0; --c) {
                    for (int k = 0; k <= c; ++k) {
                        dp[node][c] = max(dp[node][c], dp[node][c - k] + dp[child][k]);
                    }
                }
            }
            
            // Consider buying stock at this node
            int fullPrice = present[node - 1];
            int discountPrice = fullPrice / 2;
            int profit = future[node - 1] - fullPrice;
            int discountProfit = future[node - 1] - discountPrice;
            
            for (int c = budget; c >= fullPrice; --c) {
                dp[node][c] = max(dp[node][c], dp[node][c - fullPrice] + profit);
            }
            
            for (int c = budget; c >= discountPrice; --c) {
                dp[node][c] = max(dp[node][c], dp[node][c - discountPrice] + discountProfit);
            }
        };
        
        dfs(1);
        
        return *max_element(dp[1].begin(), dp[1].end());            
    }
};
