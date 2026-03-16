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
// Helpful references (internal KB):
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use when you need to explore all reachable vertices from a starting point or systematically visit all nodes in a graph or tree. It's suitable for problems requiring full exploration of a branch before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically using a stack (explicit or implicit via recursion).
//   • Invariants: Every node `v` in the graph is either visited or not yet visited.; The recursion stack (or explicit stack) always contains a path from the source node to the current node being explored.
//   • Tips: Use a `visited` array or set to prevent cycles and redundant work.; Recursion is often cleaner for implementation, but iterative DFS with an explicit stack avoids recursion depth limits.
//   • Pitfalls: Stack overflow can occur with deep recursion on large graphs.; Forgetting to mark nodes as visited leads to infinite loops in cyclic graphs.
// - Directed Graphs (graph, array, dfs, bfs)
//   • When to use: Use when modeling relationships with a specific flow direction between entities. It is ideal for determining reachability or finding paths from one or more sources.
//   • Idea: Directed graphs represent connections where edges have a specific direction, often implemented using adjacency lists. Depth-first search (DFS) and breadth-first search (BFS) are fundamental algorithms for traversing these graphs to find paths and determine reachability in O(V+E) time.
//   • Invariants: The 'visited' set accurately reflects all nodes for which traversal has been initiated.; For DFS, all nodes reachable from the current node via unvisited paths will eventually be explored.
//   • Tips: Always use a 'visited' set or array to prevent infinite loops in cycles and redundant processing.; Adjacency list representation is generally preferred for sparse graphs due to better space and time complexity for traversal.
//   • Pitfalls: Forgetting to handle cycles can lead to infinite loops or stack overflows in DFS.; Incorrectly applying algorithms designed for undirected graphs to directed graphs without modification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : hierarchy) {
            graph[edge[0]].push_back(edge[1]);
        }
        vector<int> cost(n + 1), profit(n + 1);
        for (int i = 1; i <= n; ++i) {
            cost[i] = present[i - 1];
            profit[i] = future[i - 1] - present[i - 1];
        }
        vector<long long> dp(budget + 1, LLONG_MIN);
        dp[0] = 0;
        function<void(int)> dfs = [&](int u) {
            for (int v : graph[u]) {
                dfs(v);
                for (int j = budget; j >= 0; --j) {
                    if (dp[j] == LLONG_MIN) continue;
                    int discountedCost = cost[v] / 2;
                    if (j + discountedCost <= budget) {
                        dp[j + discountedCost] = max(dp[j + discountedCost], dp[j] + profit[v]);
                    }
                }
            }
        };
        dfs(1);
        long long maxProfit = 0;
        for (long long p : dp) {
            maxProfit = max(maxProfit, p);
        }
        return maxProfit;
    }
};