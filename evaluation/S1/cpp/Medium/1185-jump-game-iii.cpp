// Source: https://leetcode.com/problems/jump-game-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [4,2,3,0,3,1,2], start = 5
// Output: true
// Explanation: 
// All possible ways to reach at index 3 with value 0 are: 
// index 5 -> index 4 -> index 1 -> index 3 
// index 5 -> index 6 -> index 4 -> index 1 -> index 3
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	0 <= arr[i] < arr.length
// 	0 <= start < arr.length
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Depth-first search (graph, array, dfs, biconnected-components)
//   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
//   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
//   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
//   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> visited(n, false);
        deque<int> dq;
        dq.push_back(start);
        visited[start] = true;

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();

            if (arr[u] == 0) return true;

            int v1 = u + arr[u];
            if (v1 >= 0 && v1 < n && !visited[v1]) {
                visited[v1] = true;
                dq.push_back(v1);
            }

            int v2 = u - arr[u];
            if (v2 >= 0 && v2 < n && !visited[v2]) {
                visited[v2] = true;
                dq.push_back(v2);
            }
        }

        return false;           
    }
};
