// Source: https://leetcode.com/problems/parallel-courses-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given a 2D integer array relations where relations[j] = [prevCoursej, nextCoursej] denotes that course prevCoursej has to be completed before course nextCoursej (prerequisite relationship). Furthermore, you are given a 0-indexed integer array time where time[i] denotes how many months it takes to complete the (i+1)th course.
//
// You must find the minimum number of months needed to complete all the courses following these rules:
//
//
// 	You may start taking a course at any time if the prerequisites are met.
// 	Any number of courses can be taken at the same time.
//
//
// Return the minimum number of months needed to complete all the courses.
//
// Note: The test cases are generated such that it is possible to complete every course (i.e., the graph is a directed acyclic graph).
//
// Example:
// Input: n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
// Output: 8
// Explanation: The figure above represents the given graph and the time required to complete each course. 
// We start course 1 and course 2 simultaneously at month 0.
// Course 1 takes 3 months and course 2 takes 2 months to complete respectively.
// Thus, the earliest time we can start course 3 is at month 3, and the total time required is 3 + 5 = 8 months.
//
// Constraints:
// 1 <= n <= 5 * 104
// 	0 <= relations.length <= min(n * (n - 1) / 2, 5 * 104)
// 	relations[j].length == 2
// 	1 <= prevCoursej, nextCoursej <= n
// 	prevCoursej != nextCoursej
// 	All the pairs [prevCoursej, nextCoursej] are unique.
// 	time.length == n
// 	1 <= time[i] <= 104
// 	The given graph is a directed acyclic graph.
//
// Helpful references (internal KB):
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Topological Sorting (graph, array, dfs, topo)
//   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
//   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
//   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
//   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<pair<int, int>>> graph(n);
        vector<int> indegree(n, 0);
        for (const auto& relation : relations) {
            int u = relation[0] - 1;
            int v = relation[1] - 1;
            graph[u].emplace_back(v, time[v]);
            indegree[v]++;
        }

        queue<int> q;
        vector<long long> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
                dp[i] = time[i];
            }
        }

        long long result = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result = max(result, dp[u]);
            for (const auto& [v, t] : graph[u]) {
                dp[v] = max(dp[v], dp[u] + t);
                if (--indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        return static_cast<int>(result);            
    }
};
