// Source: https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given three positive integers n, x, and y.
//
// In a city, there exist houses numbered 1 to n connected by n streets. There is a street connecting the house numbered i with the house numbered i + 1 for all 1 <= i <= n - 1 . An additional street connects the house numbered x with the house numbered y.
//
// For each k, such that 1 <= k <= n, you need to find the number of pairs of houses (house1, house2) such that the minimum number of streets that need to be traveled to reach house2 from house1 is k.
//
// Return a 1-indexed array result of length n where result[k] represents the total number of pairs of houses such that the minimum streets required to reach one house from the other is k.
//
// Note that x and y can be equal.
//
// Example:
// Input: n = 3, x = 1, y = 3
// Output: [6,0,0]
// Explanation: Let's look at each pair of houses:
// - For the pair (1, 2), we can go from house 1 to house 2 directly.
// - For the pair (2, 1), we can go from house 2 to house 1 directly.
// - For the pair (1, 3), we can go from house 1 to house 3 directly.
// - For the pair (3, 1), we can go from house 3 to house 1 directly.
// - For the pair (2, 3), we can go from house 2 to house 3 directly.
// - For the pair (3, 2), we can go from house 3 to house 2 directly.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= x, y <= n
//
// Helpful references (internal KB):
// - Floyd-Warshall Algorithm (number, simulation)
//   • When to use: When you need to find the shortest paths between all possible pairs of vertices in a graph. It is particularly suitable for dense graphs or when negative edge weights are present, as long as no negative cycles are reachable.
//   • Idea: Floyd-Warshall is a dynamic programming algorithm that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path distances, achieving an O(V^3) time complexity.
//   • Invariants: After the k-th iteration, dist[i][j] contains the shortest path from i to j considering only vertices 0 to k-1 as intermediate nodes.; For any pair (i, j), dist[i][j] is always greater than or equal to the true shortest path distance from i to j (or infinity if unreachable).
//   • Tips: Initialize distances: direct edge weights, infinity for no direct edge, zero for self-loops.; The outermost loop must iterate through intermediate vertices (k).
//   • Pitfalls: Incorrect loop order (k not outermost) leads to incorrect results.; Integer overflow with large path sums if not using appropriate data types.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
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
 * @param {number} n
 * @param {number} x
 * @param {number} y
 * @return {number[]}
 */
var countOfPairs = function(n, x, y) {
    // Create an adjacency matrix for the graph
    const graph = Array.from({ length: n }, () => Array(n).fill(Infinity));
    
    // Initialize the adjacency matrix with direct connections
    for (let i = 0; i < n - 1; i++) {
        graph[i][i + 1] = 1;
        graph[i + 1][i] = 1;
    }
    
    // Add the special connection between x and y
    if (x !== y) {
        graph[x][y] = 1;
        graph[y][x] = 1;
    }

    // Floyd-Warshall algorithm to compute shortest distances
    for (let k = 0; k < n; k++) {
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < n; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

    // Count pairs of houses at each distance
    const result = Array(n).fill(0);
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            const dist = graph[i][j];
            if (dist !== Infinity) {
                result[dist - 1]++;
            }
        }
    }

    return result;
};
