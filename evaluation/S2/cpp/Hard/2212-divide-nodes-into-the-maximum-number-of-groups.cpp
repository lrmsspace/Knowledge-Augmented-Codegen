// Source: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.
//
// You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
//
// Divide the nodes of the graph into m groups (1-indexed) such that:
//
//
// 	Each node in the graph belongs to exactly one group.
// 	For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
//
//
// Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
// Explanation: As shown in the image we:
// - Add node 5 to the first group.
// - Add node 1 to the second group.
// - Add nodes 2 and 4 to the third group.
// - Add nodes 3 and 6 to the fourth group.
// We can see that every edge is satisfied.
// It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
//
// Constraints:
// 1 <= n <= 500
// 	1 <= edges.length <= 104
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There is at most one edge between any pair of vertices.
//
// Helpful references (internal KB):
// - Check whether a graph is bipartite (graph, queue, bfs)
//   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
//   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
//   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
//   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
//   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
// - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
//   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
//   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
//   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
//   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
// - Finding Bridges Online (graph, tree, union-find, counting)
//   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
//   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
//   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
//   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
//   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> color(n + 1, -1);
        int maxGroups = 0;

        for (int i = 1; i <= n; ++i) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                int groupCount = 0;

                while (!q.empty()) {
                    int size = q.size();
                    ++groupCount;

                    for (int j = 0; j < size; ++j) {
                        int node = q.front();
                        q.pop();

                        for (int neighbor : graph[node]) {
                            if (color[neighbor] == -1) {
                                color[neighbor] = 1 - color[node];
                                q.push(neighbor);
                            } else if (color[neighbor] == color[node]) {
                                return -1; // Not bipartite
                            }
                        }
                    }
                }

                maxGroups += groupCount;
            }
        }

        return maxGroups;           
    }
};
