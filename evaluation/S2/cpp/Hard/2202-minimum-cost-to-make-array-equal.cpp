// Source: https://leetcode.com/problems/minimum-cost-to-make-array-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums and cost consisting each of n positive integers.
//
// You can do the following operation any number of times:
//
//
// 	Increase or decrease any element of the array nums by 1.
//
//
// The cost of doing one operation on the ith element is cost[i].
//
// Return the minimum total cost such that all the elements of the array nums become equal.
//
// Example:
// Input: nums = [1,3,5,2], cost = [2,3,1,14]
// Output: 8
// Explanation: We can make all the elements equal to 2 in the following way:
// - Increase the 0th element one time. The cost is 2.
// - Decrease the 1st element one time. The cost is 3.
// - Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
// The total cost is 2 + 3 + 3 = 8.
// It can be shown that we cannot make the array equal with a smaller cost.
//
// Constraints:
// n == nums.length == cost.length
// 	1 <= n <= 105
// 	1 <= nums[i], cost[i] <= 106
// 	Test cases are generated in a way that the output doesn't exceed 253-1
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        int n = nums.size();
        vector<pair<int, int>> pairs(n);
        for (int i = 0; i < n; ++i) {
            pairs[i] = {nums[i], cost[i]};
        }
        sort(pairs.begin(), pairs.end());

        long long totalCost = 0;
        for (const auto& p : pairs) {
            totalCost += static_cast<long long>(p.first) * p.second;
        }

        long long minTotalCost = LLONG_MAX;
        long long prefixCost = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                prefixCost += static_cast<long long>(pairs[i - 1].second);
            }
            long long currentCost = prefixCost * pairs[i].first + (totalCost - prefixCost * pairs[i].first);
            minTotalCost = min(minTotalCost, currentCost);
        }

        return minTotalCost;            
    }
};
