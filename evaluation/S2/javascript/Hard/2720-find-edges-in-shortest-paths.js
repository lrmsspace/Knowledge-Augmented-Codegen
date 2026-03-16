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
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - Minimum spanning tree - Prim's algorithm (graph, matrix, array, mst-prim, greedy)
//   • When to use: When you need to find a minimum spanning tree in a connected, weighted graph, especially efficient for dense graphs or when starting from an arbitrary vertex.
//   • Idea: Prim's algorithm is a greedy algorithm that constructs a Minimum Spanning Tree (MST) by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside it. It typically runs in O(E log V) with a priority queue or O(V^2) with an adjacency matrix.
//   • Invariants: The set of edges chosen so far forms a tree (no cycles) and connects a subset of vertices.; At each step, the chosen edge is the minimum weight edge connecting a vertex in the current MST to a vertex outside it.
//   • Tips: Initialize distances (or minimum edge weights) for all vertices not in the MST to infinity.; Use a priority queue to efficiently retrieve the minimum weight edge connecting to the current MST.
//   • Pitfalls: Failing to correctly update edge weights to neighbors when a new vertex is added to the MST.; Not handling disconnected graphs, which will result in only an MST for the starting component.
// - Finding a negative cycle in the graph (graph, matrix, floyd-warshall)
//   • When to use: Use when you need to find if a negative cycle exists in a graph, especially when dealing with all-pairs shortest paths or when edge weights can be negative. It is suitable for dense graphs.
//   • Idea: The Floyd-Warshall algorithm can detect negative cycles by checking if any vertex has a negative distance to itself after all iterations. It computes all-pairs shortest paths in O(V^3) time.
//   • Invariants: After k iterations, dist[i][j] stores the shortest path from i to j using only intermediate vertices from 0 to k-1.; For any i, dist[i][i] remains 0 unless a negative cycle involving i is found.
//   • Tips: Initialize distance matrix with edge weights or infinity for non-existent edges.; Set dist[i][i] to 0 for all i initially.
//   • Pitfalls: Incorrect initialization of the distance matrix, especially dist[i][i].; Forgetting to check the main diagonal for negative values after computation.
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
    const graph = Array.from({ length: n }, () => []);
    const edgeIndexMap = new Map();
    for (let i = 0; i < edges.length; i++) {
        const [u, v, w] = edges[i];
        graph[u].push([v, w]);
        graph[v].push([u, w]);
        edgeIndexMap.set(`${u},${v}`, i);
        edgeIndexMap.set(`${v},${u}`, i);
    }
    const result = new Array(edges.length).fill(false);
    const distances = Array.from({ length: n }, () => Infinity);
    distances[0] = 0;
    const queue = [[0, 0]];
    while (queue.length > 0) {
        const [currentNode, currentDistance] = queue.shift();
        if (currentDistance > distances[currentNode]) continue;
        for (const [neighbor, weight] of graph[currentNode]) {
            const newDistance = currentDistance + weight;
            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                queue.push([neighbor, newDistance]);
            }
        }
    }
    for (let i = 0; i < edges.length; i++) {
        const [u, v, w] = edges[i];
        if (distances[u] !== Infinity && distances[v] !== Infinity && 
            distances[u] + w === distances[v]) {
            result[i] = true;
        } else if (distances[v] !== Infinity && distances[u] !== Infinity && 
                   distances[v] + w === distances[u]) {
            result[i] = true;
        }
    }
    return result;
};
