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
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Breadth-first search (graph, array, bfs)
//   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
//   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
//   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when you need to find the shortest path (in terms of number of edges) from a source node to all other reachable nodes in an unweighted graph. It is also suitable for exploring a graph layer by layer.
//   • Idea: BFS systematically explores a graph level by level, starting from a source node, ensuring all nodes at a given distance are visited before moving to the next distance level. It operates in O(N + M) time for N vertices and M edges.
//   • Invariants: All nodes currently in the queue are at the same or adjacent distance level from the source.; The 'used' array accurately reflects all nodes that have been added to the queue for processing.
//   • Tips: Always use a queue to maintain the order of nodes to visit.; Utilize a 'visited' array or set to prevent revisiting nodes and infinite loops.
//   • Pitfalls: Does not find shortest paths in weighted graphs unless weights are 0 or 1 (use Dijkstra for general weighted graphs).; Forgetting to mark nodes as visited can lead to incorrect results or TLE.
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
    
    // Build the graph
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    
    // BFS to find shortest distance from master server (0) to all servers
    const dist = new Array(n).fill(Infinity);
    dist[0] = 0;
    const queue = [0];
    
    while (queue.length > 0) {
        const u = queue.shift();
        for (const v of graph[u]) {
            if (dist[v] === Infinity) {
                dist[v] = dist[u] + 1;
                queue.push(v);
            }
        }
    }
    
    let maxIdleTime = 0;
    
    // Calculate the time when each server becomes idle and find the maximum
    for (let i = 1; i < n; i++) {
        const roundTripTime = dist[i] * 2;
        const lastSentTime = Math.floor((roundTripTime - 1) / patience[i]) * patience[i];
        const idleTime = lastSentTime + roundTripTime + 1; // +1 for the second after receiving the reply
        maxIdleTime = Math.max(maxIdleTime, idleTime);
    }
    
    return maxIdleTime;
};
