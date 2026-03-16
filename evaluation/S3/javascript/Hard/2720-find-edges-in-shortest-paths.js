// Source: https://leetcode.com/problems/find-edges-in-shortest-paths/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted graph of n nodes numbered from 0 to n - 1. The graph consists of m edges represented by a 2D array edges, where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Consider all the shortest paths from node 0 to node n - 1 in the graph. You need to find a boolean array answer where answer[i] is true if the edge edges[i] is part of at least one shortest path. Otherwise, answer[i] is false.
//
// Return the array answer.
//
// Note that the graph may not be connected.
//
// Example:
// Input: n = 6, edges = [[0,1,4],[0,2,1],[1,3,2],[1,4,3],[1,5,1],[2,3,1],[3,5,3],[4,5,2]]
//
// Output: [true,true,true,false,true,true,true,false]
//
// Explanation:
//
// The following are all the shortest paths between nodes 0 and 5:
//
//
// 	The path 0 -> 1 -> 5: The sum of weights is 4 + 1 = 5.
// 	The path 0 -> 2 -> 3 -> 5: The sum of weights is 1 + 1 + 3 = 5.
// 	The path 0 -> 2 -> 3 -> 1 -> 5: The sum of weights is 1 + 1 + 2 + 1 = 5.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	m == edges.length
// 	1 <= m <= min(5 * 104, n * (n - 1) / 2)
// 	0 <= ai, bi < n
// 	ai != bi
// 	1 <= wi <= 105
// 	There are no repeated edges.
//
// Helpful references (internal KB):
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
// - Shortest Paths (graph, heap, dijkstra, greedy)
//   • When to use: When finding the shortest path from a single source vertex to all other vertices in a weighted graph. It is specifically applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm computes the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It uses a greedy approach with a priority queue, achieving a typical time complexity of O(E log V) or O(E + V log V).
//   • Invariants: For any vertex v extracted from the priority queue, distTo[v] is the shortest path distance from the source.; The distTo array always stores the shortest known distance from the source to each vertex found so far.
//   • Tips: Use a min-priority queue to efficiently extract the vertex with the smallest current distance.; Initialize source distance to 0 and all other distances to infinity.
//   • Pitfalls: Fails if the graph contains any negative edge weights; use Bellman-Ford or SPFA instead.; Inefficient priority queue implementation can degrade performance significantly.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {boolean[]}
 */
var findAnswer = function(n, edges) {
        // Build the graph as an adjacency list
        const graph = Array(n).fill(null).map(() => []);
        for (const [u, v, w] of edges) {
                graph[u].push([v, w]);
                graph[v].push([u, w]);
        }

        // Find shortest paths from node 0 using Dijkstra's algorithm
        const dist = Array(n).fill(Infinity);
        dist[0] = 0;
        const pq = [[0, 0]]; // [distance, node]

        while (pq.length > 0) {
                const [d, u] = pq.shift();
                if (d > dist[u]) continue;
                for (const [v, w] of graph[u]) {
                        if (dist[u] + w < dist[v]) {
                                dist[v] = dist[u] + w;
                                pq.push([dist[v], v]);
                        }
                }
        }

        // Determine which edges are part of any shortest path
        const result = Array(edges.length).fill(false);
        for (let i = 0; i < edges.length; i++) {
                const [u, v, w] = edges[i];
                if (dist[u] !== Infinity && dist[v] !== Infinity && dist[u] + w === dist[v]) {
                        result[i] = true;
                } else if (dist[v] !== Infinity && dist[u] !== Infinity && dist[v] + w === dist[u]) {
                        result[i] = true;
                }
        }

        return result;
};
