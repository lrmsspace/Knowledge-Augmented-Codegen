// Source: https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag/   |   Difficulty: Hard
//
// Problem Description:
// You are given a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1, represented by a 2D array edges, where edges[i] = [ui, vi] indicates a directed edge from node ui to vi. Each node has an associated score given in an array score, where score[i] represents the score of node i.
//
// You must process the nodes in a valid topological order. Each node is assigned a 1-based position in the processing order.
//
// The profit is calculated by summing up the product of each node's score and its position in the ordering.
//
// Return the maximum possible profit achievable with an optimal topological order.
//
// A topological order of a DAG is a linear ordering of its nodes such that for every directed edge u → v, node u comes before v in the ordering.
//
// Example:
// Input: n = 2, edges = [[0,1]], score = [2,3]
//
// Output: 8
//
// Explanation:
//
//
//
// Node 1 depends on node 0, so a valid order is [0, 1].
//
//
// 	
// 		
// 			Node
// 			Processing Order
// 			Score
// 			Multiplier
// 			Profit Calculation
// 		
// 	
// 	
// 		
// 			0
// 			1st
// 			2
// 			1
// 			2 × 1 = 2
// 		
// 		
// 			1
// 			2nd
// 			3
// 			2
// 			3 × 2 = 6
// 		
// 	
//
//
// The maximum total profit achievable over all valid topological orders is 2 + 6 = 8.
//
// Constraints:
// 1 <= n == score.length <= 22
// 	1 <= score[i] <= 105
// 	0 <= edges.length <= n * (n - 1) / 2
// 	edges[i] == [ui, vi] denotes a directed edge from ui to vi.
// 	0 <= ui, vi < n
// 	ui != vi
// 	The input graph is guaranteed to be a DAG.
// 	There are no duplicate edges.
//
// Helpful references (internal KB):
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Directed Graphs (graph, array, dfs, bfs)
//   • When to use: Use when modeling relationships with a specific flow direction between entities. It is ideal for determining reachability or finding paths from one or more sources.
//   • Idea: Directed graphs represent connections where edges have a specific direction, often implemented using adjacency lists. Depth-first search (DFS) and breadth-first search (BFS) are fundamental algorithms for traversing these graphs to find paths and determine reachability in O(V+E) time.
//   • Invariants: The 'visited' set accurately reflects all nodes for which traversal has been initiated.; For DFS, all nodes reachable from the current node via unvisited paths will eventually be explored.
//   • Tips: Always use a 'visited' set or array to prevent infinite loops in cycles and redundant processing.; Adjacency list representation is generally preferred for sparse graphs due to better space and time complexity for traversal.
//   • Pitfalls: Forgetting to handle cycles can lead to infinite loops or stack overflows in DFS.; Incorrectly applying algorithms designed for undirected graphs to directed graphs without modification.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<vector<int>> graph(n);
        vector<int> in_degree(n, 0);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            in_degree[edge[1]]++;
        }
        vector<int> order;
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : graph[u]) {
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        long long profit = 0;
        for (int i = 0; i < n; ++i) {
            profit += static_cast<long long>(score[order[i]]) * (i + 1);
        }
        return profit;
    }
};
