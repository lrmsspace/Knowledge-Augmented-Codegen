// Source: https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/   |   Difficulty: Medium
//
// Problem Description:
// Given a directed acyclic graph, with n vertices numbered from 0 to n-1, and an array edges where edges[i] = [fromi, toi] represents a directed edge from node fromi to node toi.
//
// Find the smallest set of vertices from which all nodes in the graph are reachable. It's guaranteed that a unique solution exists.
//
// Notice that you can return the vertices in any order.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
// Output: [0,3]
// Explanation: It's not possible to reach all the nodes from a single vertex. From 0 we can reach [0,1,2,5]. From 3 we can reach [3,4,2,5]. So we output [0,3].
//
// Constraints:
// 2 <= n <= 10^5
// 	1 <= edges.length <= min(10^5, n * (n - 1) / 2)
// 	edges[i].length == 2
// 	0 <= fromi, toi < n
// 	All pairs (fromi, toi) are distinct.
//
// Helpful references (internal KB):
// - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
//   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
//   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
//   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
//   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
// - Strongly connected components and the condensation graph (graph, enumeration)
//   • When to use: When you need to identify maximal subgraphs where all vertices are mutually reachable, or to simplify a directed graph into a Directed Acyclic Graph (DAG) of components for further processing.
//   • Idea: This concept defines SCCs as maximal vertex subsets in a directed graph where all pairs are mutually reachable. It also introduces the condensation graph, which represents SCCs as nodes and forms a DAG, typically found in O(V+E) time.
//   • Invariants: Every vertex belongs to exactly one strongly connected component.; Within any SCC, a path exists from any vertex u to any other vertex v, and vice-versa.
//   • Tips: Understand that SCCs partition the graph's vertices.; The condensation graph is always a Directed Acyclic Graph (DAG).
//   • Pitfalls: Confusing SCCs with simple cycles or connected components in undirected graphs.; Incorrectly assuming the condensation graph has cycles.
// - Shortest Paths (graph, topo, dp-1d)
//   • When to use: This algorithm finds the shortest paths from a single source vertex to all other vertices in a directed acyclic graph (DAG) with arbitrary edge weights.
//   • Idea: This algorithm computes single-source shortest paths in a Directed Acyclic Graph (DAG) by processing vertices in topological order, relaxing outgoing edges. It achieves a time complexity of O(V + E).
//   • Invariants: The distance to the source vertex, distTo[s], remains 0 throughout the algorithm.; For any vertex v, distTo[v] always stores the shortest path found so far from s to v.
//   • Tips: First, perform a topological sort on the DAG to determine the processing order.; Initialize all distances to infinity, except the source vertex which is zero.
//   • Pitfalls: Applying this algorithm to a graph containing cycles will yield incorrect results.; An incorrect topological sort order will lead to incorrect shortest path calculations.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> inDegree(n, 0);
        for (const auto& edge : edges) {
            inDegree[edge[1]]++;
        }

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                result.push_back(i);
            }
        }

        return result;          
    }
};
