// Source: https://leetcode.com/problems/minimum-sideway-jumps/   |   Difficulty: Medium
//
// Problem Description:
// There is a 3 lane road of length n that consists of n + 1 points labeled from 0 to n. A frog starts at point 0 in the second lane and wants to jump to point n. However, there could be obstacles along the way.
//
// You are given an array obstacles of length n + 1 where each obstacles[i] (ranging from 0 to 3) describes an obstacle on the lane obstacles[i] at point i. If obstacles[i] == 0, there are no obstacles at point i. There will be at most one obstacle in the 3 lanes at each point.
//
//
// 	For example, if obstacles[2] == 1, then there is an obstacle on lane 1 at point 2.
//
//
// The frog can only travel from point i to point i + 1 on the same lane if there is not an obstacle on the lane at point i + 1. To avoid obstacles, the frog can also perform a side jump to jump to another lane (even if they are not adjacent) at the same point if there is no obstacle on the new lane.
//
//
// 	For example, the frog can jump from lane 3 at point 3 to lane 1 at point 3.
//
//
// Return the minimum number of side jumps the frog needs to reach any lane at point n starting from lane 2 at point 0.
//
// Note: There will be no obstacles on points 0 and n.
//
// Example:
// Input: obstacles = [0,1,2,3,0]
// Output: 2 
// Explanation: The optimal solution is shown by the arrows above. There are 2 side jumps (red arrows).
// Note that the frog can jump over obstacles only when making side jumps (as shown at point 2).
//
// Constraints:
// obstacles.length == n + 1
// 	1 <= n <= 5 * 105
// 	0 <= obstacles[i] <= 3
// 	obstacles[0] == obstacles[n] == 0
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minSideJumps(int* obstacles, int obstaclesSize) {
    int n = obstaclesSize - 1;
    int dp[3] = {1, 0, 1}; // dp[i]: min side jumps to reach lane i+1 at current position

    for (int i = 1; i <= n; ++i) {
        // Mark lanes with obstacles as unreachable
        for (int lane = 0; lane < 3; ++lane) {
            if (obstacles[i] == lane + 1) {
                dp[lane] = 1e9; // Use a large number to represent infinity
            }
        }

        // Find the minimum side jumps among reachable lanes
        int min_jumps = 1e9;
        for (int lane = 0; lane < 3; ++lane) {
            if (dp[lane] < min_jumps) {
                min_jumps = dp[lane];
            }
        }

        // Update dp for lanes without obstacles
        for (int lane = 0; lane < 3; ++lane) {
            if (obstacles[i] != lane + 1) {
                dp[lane] = (dp[lane] < min_jumps + 1) ? dp[lane] : min_jumps + 1;
            }
        }
    }

    // Find the minimum side jumps to reach point n
    int result = dp[0];
    for (int lane = 1; lane < 3; ++lane) {
        if (dp[lane] < result) {
            result = dp[lane];
        }
    }

    return result;      
}
