// Source: https://leetcode.com/problems/sum-of-distances-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
// Output: [8,12,6,10,10,10]
// Explanation: The tree is shown above.
// We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
// equals 1 + 1 + 2 + 2 + 2 = 8.
// Hence, answer[0] = 8, and so on.
//
// Constraints:
// 1 <= n <= 3 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	The given input represents a valid tree.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Finding Bridges Online (ds, tree, union-find, lca, rerooting)
//   • When to use: Use this algorithm to dynamically maintain bridges and 2-edge-connected components in a graph as edges are added. It efficiently processes edge additions by updating forest structures and compressing cycles.
//   • Idea: This algorithm dynamically maintains bridges and 2-edge-connected components using two DSU structures and a parent array for tree structure. Edge additions involve re-rooting smaller trees and compressing cycles via LCA, achieving amortized O(log N) per edge operation.
//   • Invariants: The par[] array always defines a forest structure where each tree corresponds to a connected component of 2-edge-connected components.; Each 2-edge-connected component is represented by a single canonical element in its dedicated DSU structure.
//   • Tips: Employ two DSU structures: one for connected components and another for 2-edge-connected components.; Optimize re-rooting operations by always re-rooting the smaller of the two trees being joined.
//   • Pitfalls: Failing to consistently update both DSU structures and the parent array after operations.; Incorrectly handling parent pointers during re-rooting, leading to broken tree structures.
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private void dfs(int node, int parent, List<Set<Integer>> graph, int[] count, int[] res) {
        for (int neighbor : graph.get(node)) {
            if (neighbor == parent) continue;
            dfs(neighbor, node, graph, count, res);
            count[node] += count[neighbor];
            res[node] += res[neighbor] + count[neighbor];
        }
        count[node] += 1;
    }
    private void dfs2(int node, int parent, List<Set<Integer>> graph, int[] count, int[] res, int n) {
        for (int neighbor : graph.get(node)) {
            if (neighbor == parent) continue;
            res[neighbor] = res[node] - count[neighbor] + (n - count[neighbor]);
            dfs2(neighbor, node, graph, count, res, n);
        }
    }
    public int[] sumOfDistancesInTree(int n, int[][] edges) {
        List<Set<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new HashSet<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        int[] count = new int[n];
        int[] res = new int[n];

        dfs(0, -1, graph, count, res);
        dfs2(0, -1, graph, count, res, n);

        return res;         
    }
}
