// Source: https://leetcode.com/problems/the-time-when-the-network-becomes-idle/   |   Difficulty: Medium
//
// Problem Description:
// There is a network of n servers, labeled from 0 to n - 1. You are given a 2D integer array edges, where edges[i] = [ui, vi] indicates there is a message channel between servers ui and vi, and they can pass any number of messages to each other directly in one second. You are also given a 0-indexed integer array patience of length n.
//
// All servers are connected, i.e., a message can be passed from one server to any other server(s) directly or indirectly through the message channels.
//
// The server labeled 0 is the master server. The rest are data servers. Each data server needs to send its message to the master server for processing and wait for a reply. Messages move between servers optimally, so every message takes the least amount of time to arrive at the master server. The master server will process all newly arrived messages instantly and send a reply to the originating server via the reversed path the message had gone through.
//
// At the beginning of second 0, each data server sends its message to be processed. Starting from second 1, at the beginning of every second, each data server will check if it has received a reply to the message it sent (including any newly arrived replies) from the master server:
//
//
// 	If it has not, it will resend the message periodically. The data server i will resend the message every patience[i] second(s), i.e., the data server i will resend the message if patience[i] second(s) have elapsed since the last time the message was sent from this server.
// 	Otherwise, no more resending will occur from this server.
//
//
// The network becomes idle when there are no messages passing between servers or arriving at servers.
//
// Return the earliest second starting from which the network becomes idle.
//
// Example:
// Input: edges = [[0,1],[1,2]], patience = [0,2,1]
// Output: 8
// Explanation:
// At (the beginning of) second 0,
// - Data server 1 sends its message (denoted 1A) to the master server.
// - Data server 2 sends its message (denoted 2A) to the master server.
//
// At second 1,
// - Message 1A arrives at the master server. Master server processes message 1A instantly and sends a reply 1A back.
// - Server 1 has not received any reply. 1 second (1 < patience[1] = 2) elapsed since this server has sent the message, therefore it does not resend the message.
// - Server 2 has not received any reply. 1 second (1 == patience[2] = 1) elapsed since this server has sent the message, therefore it resends the message (denoted 2B).
//
// At second 2,
// - The reply 1A arrives at server 1. No more resending will occur from server 1.
// - Message 2A arrives at the master server. Master server processes message 2A instantly and sends a reply 2A back.
// - Server 2 resends the message (denoted 2C).
// ...
// At second 4,
// - The reply 2A arrives at server 2. No more resending will occur from server 2.
// ...
// At second 7, reply 2D arrives at server 2.
//
// Starting from the beginning of the second 8, there are no messages passing between servers or arriving at servers.
// This is the time when the network becomes idle.
//
// Constraints:
// n == patience.length
// 	2 <= n <= 105
// 	patience[0] == 0
// 	1 <= patience[i] <= 105 for 1 <= i < n
// 	1 <= edges.length <= min(105, n * (n - 1) / 2)
// 	edges[i].length == 2
// 	0 <= ui, vi < n
// 	ui != vi
// 	There are no duplicate edges.
// 	Each server can directly or indirectly reach another server.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Maximum flow - Push-relabel method improved (graph, array, greedy, bfs)
//   • When to use: Use this for maximum flow problems on graphs where an optimized push-relabel approach is required. It improves performance by prioritizing vertices with the greatest height for push and relabel operations.
//   • Idea: This algorithm is an optimized variant of the push-relabel maximum flow method, which improves efficiency by always selecting the vertex with the greatest height that has excess flow. This specific vertex selection strategy leads to a better theoretical time complexity, typically O(V^2 * sqrt(E)) or O(V^3) depending on implementation details.
//   • Invariants: For any edge (u, v) in the residual graph, h(u) <= h(v) + 1.; The total excess flow in the network is always non-negative.
//   • Tips: Always select the active vertex with the highest current height.; Maintain a data structure (e.g., buckets or lists) to quickly find highest-height vertices.
//   • Pitfalls: Incorrectly managing the list of highest-height vertices.; Failing to update residual capacities after a push operation.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges
 * @param {number[]} patience
 * @return {number}
 */
var networkBecomesIdle = function(edges, patience) {
    const n = patience.length;
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    
    const distances = Array(n).fill(Infinity);
    distances[0] = 0;
    const queue = [0];
    while (queue.length) {
        const node = queue.shift();
        for (const neighbor of graph[node]) {
            if (distances[neighbor] === Infinity) {
                distances[neighbor] = distances[node] + 1;
                queue.push(neighbor);
            }
        }
    }
    
    let maxTime = 0;
    for (let i = 1; i < n; i++) {
        const roundTrips = 2 * distances[i];
        const lastSentTime = Math.floor((roundTrips - 1) / patience[i]) * patience[i];
        const totalTime = lastSentTime + roundTrips;
        maxTime = Math.max(maxTime, totalTime);
    }
    
    return maxTime + 1; // Network becomes idle at the beginning of the next second
};
