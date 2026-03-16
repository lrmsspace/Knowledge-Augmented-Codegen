// Source: https://leetcode.com/problems/longest-special-path-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node in which all node values are distinct, except for at most one value that may appear twice.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,1],[1,2,3],[1,3,1],[2,4,6],[4,7,2],[3,5,2],[3,6,5],[6,8,3]], nums = [1,1,0,3,1,2,1,1,0]
//
// Output: [9,3]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums.
//
//
//
// The longest special paths are 1 -> 2 -> 4 and 1 -> 3 -> 6 -> 8, both having a length of 9. The minimum number of nodes across all longest special paths is 3.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= lengthi <= 103
// 	nums.length == n
// 	0 <= nums[i] <= 5 * 104
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Depth-first search (graph, array, dfs)
//   • When to use: Use when exploring all reachable nodes from a starting point, detecting cycles, or performing a topological sort on a graph. It's suitable for problems requiring deep exploration before backtracking.
//   • Idea: Depth-first search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically runs in O(V + E) time for graphs and O(V) for trees.
//   • Invariants: For any visited node 'u', 'marked[u]' is true.; If a path exists from source 's' to 'v', then DFS from 's' will eventually mark 'v'.
//   • Tips: Use a 'visited' array or set to prevent infinite loops in cyclic graphs.; Maintain a 'parent' or 'edgeTo' array for path reconstruction or cycle detection.
//   • Pitfalls: Stack overflow with deep recursion on large graphs.; Incorrectly handling cycles in undirected graphs without parent tracking.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], length = edge[2];
            graph[u].emplace_back(v, length);
            graph[v].emplace_back(u, length);
        }

        vector<int> result(2, 0);
        vector<int> freq(50001, 0);

        function<void(int, int, int, int, int)> dfs = [&](int node, int parent, int currLength, int currNodes, int usedDuplicate) {
            freq[nums[node]]++;
            if (freq[nums[node]] == 2) usedDuplicate++;

            if (usedDuplicate <= 1) {
                if (currLength > result[0]) {
                    result[0] = currLength;
                    result[1] = currNodes;
                } else if (currLength == result[0]) {
                    result[1] = min(result[1], currNodes);
                }

                for (const auto& [neighbor, length] : graph[node]) {
                    if (neighbor != parent) {
                        dfs(neighbor, node, currLength + length, currNodes + 1, usedDuplicate);
                    }
                }
            }

            freq[nums[node]]--;
        };

        dfs(0, -1, 0, 1, 0);
        return result;          
    }
};
