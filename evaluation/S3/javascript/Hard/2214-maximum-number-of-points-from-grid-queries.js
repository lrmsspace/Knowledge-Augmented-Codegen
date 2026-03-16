// Source: https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid and an array queries of size k.
//
// Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:
//
//
// 	If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
// 	Otherwise, you do not get any points, and you end this process.
//
//
// After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.
//
// Return the resulting array answer.
//
// Example:
// Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
// Output: [5,8,1]
// Explanation: The diagrams above show which cells we visit to get points for each query.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	k == queries.length
// 	1 <= k <= 104
// 	1 <= grid[i][j], queries[i] <= 106
//
// Helpful references (internal KB):
// - Dijkstra on sparse graphs (heap, dijkstra)
//   • When to use: When finding the shortest paths from a single source to all other nodes in a graph with non-negative edge weights, especially when the graph is sparse. It offers optimal time complexity for such scenarios.
//   • Idea: This algorithm finds the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights. By using a priority queue (like a Fibonacci heap), it achieves an optimal time complexity of O(E + V log V) for sparse graphs.
//   • Invariants: All vertices in the priority queue have a tentative distance from the source.; For any vertex already extracted from the priority queue, its distance is finalized and represents the shortest path.
//   • Tips: Use a priority queue (min-heap) to efficiently extract the minimum distance vertex.; Initialize distances to infinity and source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights.; Incorrectly updating distances can lead to suboptimal paths.
// - Shortest Paths (graph, heap, dijkstra, greedy)
//   • When to use: When finding the shortest path from a single source vertex to all other vertices in a weighted graph. It is specifically applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm computes the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It uses a greedy approach with a priority queue, achieving a typical time complexity of O(E log V) or O(E + V log V).
//   • Invariants: For any vertex v extracted from the priority queue, distTo[v] is the shortest path distance from the source.; The distTo array always stores the shortest known distance from the source to each vertex found so far.
//   • Tips: Use a min-priority queue to efficiently extract the vertex with the smallest current distance.; Initialize source distance to 0 and all other distances to infinity.
//   • Pitfalls: Fails if the graph contains any negative edge weights; use Bellman-Ford or SPFA instead.; Inefficient priority queue implementation can degrade performance significantly.
// - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
//   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
//   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
//   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
//   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @param {number[]} queries
 * @return {number[]}
 */
var maxPoints = function(grid, queries) {
    const m = grid.length;
    const n = grid[0].length;
    const k = queries.length;   
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const visited = Array.from({ length: m }, () => Array(n).fill(false));
    const points = Array(k).fill(0);
        
    const pq = new MinPriorityQueue({ priority: (cell) => cell.value });
    pq.enqueue({ x: 0, y: 0, value: grid[0][0] });
    visited[0][0] = true;   
    let currentPoints = 0;
    let queryIndex = 0;
    while (!pq.isEmpty() && queryIndex < k) {
        const { x, y, value } = pq.dequeue().element;
        while (queryIndex < k && queries[queryIndex] > value) {
            points[queryIndex] = currentPoints;
            queryIndex++;
        }
        currentPoints++;
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;

            if (newX >= 0 && newX < m && newY >= 0 && newY < n && !visited[newX][newY]) {
                visited[newX][newY] = true;
                pq.enqueue({ x: newX, y: newY, value: grid[newX][newY] });
            }
        }
    }   
    while (queryIndex < k) {
        points[queryIndex] = currentPoints;
        queryIndex++;
    }
    return points;
    
};
