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
// - Bellman-Ford Algorithm (graph, array, bellman-ford, dp-1d)
//   • When to use: Finds single-source shortest paths in a weighted directed graph, especially when negative edge weights are present. It can also detect negative cycles reachable from the source.
//   • Idea: Bellman-Ford iteratively relaxes all edges n-1 times to find single-source shortest paths in a weighted directed graph. It runs in O(VE) time and can detect negative cycles.
//   • Invariants: After k phases, dist[u] holds the shortest path length from source to u using at most k edges.; For any edge (u, v) with weight w, dist[v] <= dist[u] + w if dist[u] is finite and v is reachable.
//   • Tips: Initialize source distance to 0 and all other distances to infinity.; Perform exactly n-1 full passes, relaxing all edges in each pass.
//   • Pitfalls: Incorrectly handling unreachable vertices (distances remaining infinity).; Not detecting negative cycles when they exist, leading to incorrect path lengths.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
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
        vector<vector<int>> graph(n);
        vector<int> indegree(n, 0);
        for (const auto& relation : relations) {
            int prevCourse = relation[0] - 1;
            int nextCourse = relation[1] - 1;
            graph[prevCourse].push_back(nextCourse);
            indegree[nextCourse]++;
        }

        queue<int> q;
        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
                dp[i] = time[i];
            }
        }

        int maxTime = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            maxTime = max(maxTime, dp[course]);
            for (int nextCourse : graph[course]) {
                dp[nextCourse] = max(dp[nextCourse], dp[course] + time[nextCourse]);
                if (--indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }

        return maxTime;         
    }
};
