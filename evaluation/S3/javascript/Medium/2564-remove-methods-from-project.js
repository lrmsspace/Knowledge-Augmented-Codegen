// Source: https://leetcode.com/problems/remove-methods-from-project/   |   Difficulty: Medium
//
// Problem Description:
// You are maintaining a project that has n methods numbered from 0 to n - 1.
//
// You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates that method ai invokes method bi.
//
// There is a known bug in method k. Method k, along with any method invoked by it, either directly or indirectly, are considered suspicious and we aim to remove them.
//
// A group of methods can only be removed if no method outside the group invokes any methods within it.
//
// Return an array containing all the remaining methods after removing all the suspicious methods. You may return the answer in any order. If it is not possible to remove all the suspicious methods, none should be removed.
//
// Example:
// Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
//
// Output: [0,1,2,3]
//
// Explanation:
//
//
//
// Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= k <= n - 1
// 	0 <= invocations.length <= 2 * 105
// 	invocations[i] == [ai, bi]
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	invocations[i] != invocations[j]
//
// Helpful references (internal KB):
// - Directed Graphs (graph, array, dfs, bfs)
//   • When to use: Use when modeling relationships with a specific flow direction between entities. It is ideal for determining reachability or finding paths from one or more sources.
//   • Idea: Directed graphs represent connections where edges have a specific direction, often implemented using adjacency lists. Depth-first search (DFS) and breadth-first search (BFS) are fundamental algorithms for traversing these graphs to find paths and determine reachability in O(V+E) time.
//   • Invariants: The 'visited' set accurately reflects all nodes for which traversal has been initiated.; For DFS, all nodes reachable from the current node via unvisited paths will eventually be explored.
//   • Tips: Always use a 'visited' set or array to prevent infinite loops in cycles and redundant processing.; Adjacency list representation is generally preferred for sparse graphs due to better space and time complexity for traversal.
//   • Pitfalls: Forgetting to handle cycles can lead to infinite loops or stack overflows in DFS.; Incorrectly applying algorithms designed for undirected graphs to directed graphs without modification.
// - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
//   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
//   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
//   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
//   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
// - Directed Graphs (graph, matrix, dfs)
//   • When to use: Use when needing to determine reachability between all pairs of vertices in a directed graph, especially for small or dense graphs where O(V*(V+E)) time is acceptable.
//   • Idea: This approach determines all-pairs reachability in a directed graph by performing a Depth-First Search starting from each vertex. It has a time complexity of O(V*(V+E)) and a space complexity of O(V^2).
//   • Invariants: For any vertex u, after its dedicated DFS completes, TC[u][v] is true for all v reachable from u.; The transitive closure matrix TC accurately reflects all-pairs reachability in the original graph.
//   • Tips: Initialize a boolean matrix to store reachability results.; For each vertex, perform a full DFS to mark all nodes reachable from it.
//   • Pitfalls: High time complexity O(V*(V+E)) makes it unsuitable for large sparse graphs.; High space complexity O(V^2) can be prohibitive for graphs with many vertices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} k
 * @param {number[][]} invocations
 * @return {number[]}
 */
var remainingMethods = function(n, k, invocations) {
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v] of invocations) {
        graph[u].push(v);
    }
    const visited = new Array(n).fill(false);
    const dfs = (node) => {
        visited[node] = true;
        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    };
    dfs(k);
    const result = [];
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            result.push(i);
        }
    }
    return result;
};
