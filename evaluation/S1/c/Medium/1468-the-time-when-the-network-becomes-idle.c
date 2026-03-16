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
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Edge connectivity / Vertex connectivity (graph, enumeration)
//   • When to use: Used to quantify a graph's resilience by finding the minimum number of edges or vertices whose removal disconnects it, or separates a specific pair of nodes.
//   • Idea: Edge connectivity is the minimum edges to disconnect a graph, while vertex connectivity is for vertices. Both are often computed using max-flow min-cut theorems, typically in polynomial time.
//   • Invariants: The flow through any edge in the network does not exceed its capacity.; For any intermediate vertex (not source or sink), the total incoming flow equals the total outgoing flow.
//   • Tips: Edge connectivity between two specific vertices can be found using a max-flow min-cut algorithm.; To find global edge connectivity, iterate over all pairs of vertices or use specialized algorithms.
//   • Pitfalls: Confusing edge connectivity (edges) with vertex connectivity (vertices) requirements.; Incorrectly applying max-flow for global connectivity without considering all relevant source-sink pairs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int networkBecomesIdle(int** edges, int edgesSize, int* edgesColSize, int* patience, int patienceSize) {
    // Build the adjacency list for the graph
    int n = patienceSize;
    int** graph = (int**)malloc(n * sizeof(int*));
    int* graphColSize = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int)); // Max possible size
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][graphColSize[u]++] = v;
        graph[v][graphColSize[v]++] = u;
    }

    // BFS to find shortest distances from node 0
    int* dist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dist[i] = -1;
    dist[0] = 0;

    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;
    queue[back++] = 0;

    while (front < back) {
        int node = queue[front++];
        for (int i = 0; i < graphColSize[node]; i++) {
            int neighbor = graph[node][i];
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                queue[back++] = neighbor;
            }
        }
    }

    // Calculate the time when the network becomes idle
    int maxTime = 0;
    for (int i = 1; i < n; i++) {
        int roundTripTime = dist[i] * 2;
        int lastSentTime;
        if (roundTripTime <= patience[i]) {
            lastSentTime = 0;
        } else {
            lastSentTime = ((roundTripTime - 1) / patience[i]) * patience[i];
        }
        int totalTime = lastSentTime + roundTripTime;
        if (totalTime > maxTime) {
            maxTime = totalTime;
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphColSize);
    free(dist);     
    free(queue);
    return maxTime + 1;
}
