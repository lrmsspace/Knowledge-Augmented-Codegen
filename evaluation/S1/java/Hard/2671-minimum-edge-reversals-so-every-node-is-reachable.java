// Source: https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// There is a simple directed graph with n nodes labeled from 0 to n - 1. The graph would form a tree if its edges were bi-directional.
//
// You are given an integer n and a 2D integer array edges, where edges[i] = [ui, vi] represents a directed edge going from node ui to node vi.
//
// An edge reversal changes the direction of an edge, i.e., a directed edge going from node ui to node vi becomes a directed edge going from node vi to node ui.
//
// For every node i in the range [0, n - 1], your task is to independently calculate the minimum number of edge reversals required so it is possible to reach any other node starting from node i through a sequence of directed edges.
//
// Return an integer array answer, where answer[i] is the  minimum number of edge reversals required so it is possible to reach any other node starting from node i through a sequence of directed edges.
//
// Example:
// Input: n = 4, edges = [[2,0],[2,1],[1,3]]
// Output: [1,1,0,2]
// Explanation: The image above shows the graph formed by the edges.
// For node 0: after reversing the edge [2,0], it is possible to reach any other node starting from node 0.
// So, answer[0] = 1.
// For node 1: after reversing the edge [2,1], it is possible to reach any other node starting from node 1.
// So, answer[1] = 1.
// For node 2: it is already possible to reach any other node starting from node 2.
// So, answer[2] = 0.
// For node 3: after reversing the edges [1,3] and [2,1], it is possible to reach any other node starting from node 3.
// So, answer[3] = 2.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ui == edges[i][0] < n
// 	0 <= vi == edges[i][1] < n
// 	ui != vi
// 	The input is generated such that if the edges were bi-directional, the graph would be a tree.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Second Best Minimum Spanning Tree (graph, tree, enumeration)
//   • When to use: Use this when you need to identify an alternative network configuration that is marginally more expensive than the optimal one, or for robustness analysis in network design.
//   • Idea: This algorithm identifies the spanning tree with the second minimum total edge weight by finding the primary MST and then systematically replacing one MST edge with a non-MST edge. The overall time complexity is typically O(E log E + E log V).
//   • Invariants: The primary MST T always connects all vertices with minimum total weight.; Any candidate second-best MST T' is a spanning tree with exactly V-1 edges.
//   • Tips: First compute the primary MST using Kruskal's or Prim's algorithm.; For each non-MST edge (u, v), adding it to the MST creates a unique cycle.
//   • Pitfalls: Incorrectly identifying the heaviest edge on the cycle formed by adding a non-MST edge.; Forgetting to handle disconnected graphs (MST implies connected).
// - Strong Orientation (graph, tree, dfs)
//   • When to use: Use this when you need to convert an undirected, bridgeless, and connected graph into a strongly connected directed graph, ensuring reachability between any two vertices.
//   • Idea: This algorithm transforms a bridgeless, connected undirected graph into a strongly connected directed graph by performing a Depth-First Search. It orients DFS tree edges away from the root and back edges towards ancestors, achieving strong connectivity in O(V+E) time.
//   • Invariants: All DFS tree edges discovered so far are oriented from parent to child.; All back edges discovered so far are oriented from child to ancestor.
//   • Tips: Verify the input graph is connected and bridgeless before applying the algorithm.; During DFS, mark visited vertices and track parent-child relationships to distinguish edge types.
//   • Pitfalls: Applying to a graph with bridges will result in a non-strongly connected graph.; Incorrectly identifying or orienting back edges can break the strong connectivity property.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] minEdgeReversals(int n, int[][] edges) {
        List<int[]>[] graph = new List[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            graph[edge[0]].add(new int[]{edge[1], 0}); // original direction
            graph[edge[1]].add(new int[]{edge[0], 1}); // reversed direction
        }

        int[] res = new int[n];
        boolean[] visited = new boolean[n];
        visited[0] = true;
        dfs(graph, 0, visited, res);

        visited = new boolean[n];
        visited[0] = true;
        dfs2(graph, 0, visited, res);

        return res;         
    }
}
