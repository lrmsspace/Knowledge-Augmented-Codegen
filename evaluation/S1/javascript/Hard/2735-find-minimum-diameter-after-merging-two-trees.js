// Source: https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/   |   Difficulty: Hard
//
// Problem Description:
// There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
//
// You must connect one node from the first tree with another node from the second tree with an edge.
//
// Return the minimum possible diameter of the resulting tree.
//
// The diameter of a tree is the length of the longest path between any two nodes in the tree.
//
// Example:
// Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
//
// Output: 3
//
// Explanation:
//
// We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.
//
// Constraints:
// 1 <= n, m <= 105
// 	edges1.length == n - 1
// 	edges2.length == m - 1
// 	edges1[i].length == edges2[i].length == 2
// 	edges1[i] = [ai, bi]
// 	0 <= ai, bi < n
// 	edges2[i] = [ui, vi]
// 	0 <= ui, vi < m
// 	The input is generated such that edges1 and edges2 represent valid trees.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Finding the Eulerian path in O(M) (graph, eulerian-circuit, dfs)
//   • When to use: Use when you need to find a path or cycle that traverses every edge exactly once in a given graph. It's applicable when specific vertex degree conditions are met for path or cycle existence.
//   • Idea: This algorithm constructs an Eulerian path or cycle by first verifying vertex degree conditions and graph connectivity, then performing a recursive DFS-like traversal to build the path. It achieves a time complexity of O(M), where M is the number of edges.
//   • Invariants: Every edge in the constructed path has been traversed exactly once.; All edges incident to the current vertex have been explored or are part of the remaining graph.
//   • Tips: Verify graph connectivity, ignoring isolated vertices.; For an Eulerian path, ensure exactly two vertices have odd degrees.
//   • Pitfalls: Failing to check graph connectivity before starting.; Incorrectly counting odd degree vertices for path vs. cycle.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges1
 * @param {number[][]} edges2
 * @return {number}
 */
var minimumDiameterAfterMerge = function(edges1, edges2) {
    const n = edges1.length + 1;
    const m = edges2.length + 1;

    const buildGraph = (edges, size) => {
        const graph = Array.from({ length: size }, () => []);
        for (const [u, v] of edges) {
            graph[u].push(v);
            graph[v].push(u);
        }
        return graph;
    };

    const graph1 = buildGraph(edges1, n);
    const graph2 = buildGraph(edges2, m);

    const bfs = (graph, start) => {
        const queue = [start];
        const visited = new Array(graph.length).fill(false);
        visited[start] = true;
        let lastNode = start;

        while (queue.length) {
            lastNode = queue.shift();
            for (const neighbor of graph[lastNode]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
        return lastNode;
    };

    const diameter = (graph) => {
        const farthestNode = bfs(graph, 0);
        const otherFarthestNode = bfs(graph, farthestNode);
        return bfs(graph, otherFarthestNode);
    };

    const diameter1 = diameter(graph1);
    const diameter2 = diameter(graph2);

    return Math.max(diameter1 + diameter2 + 1, Math.max(diameter1, diameter2));
};
