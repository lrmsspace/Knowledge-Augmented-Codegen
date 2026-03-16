// Source: https://leetcode.com/problems/map-of-highest-peak/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer matrix isWater of size m x n that represents a map of land and water cells.
//
//
// 	If isWater[i][j] == 0, cell (i, j) is a land cell.
// 	If isWater[i][j] == 1, cell (i, j) is a water cell.
//
//
// You must assign each cell a height in a way that follows these rules:
//
//
// 	The height of each cell must be non-negative.
// 	If the cell is a water cell, its height must be 0.
// 	Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
//
// Find an assignment of heights such that the maximum height in the matrix is maximized.
//
// Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.
//
// Example:
// Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
// Explanation: The image shows the assigned heights of each cell.
// The blue cell is the water cell, and the green cells are the land cells.
//
// Constraints:
// m == isWater.length
// 	n == isWater[i].length
// 	1 <= m, n <= 1000
// 	isWater[i][j] is 0 or 1.
// 	There is at least one water cell.
//
//
//  
// Note: This question is the same as 542: https://leetcode.com/problems/01-matrix/
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when you need to find the shortest path (in terms of number of edges) from a source node to all other reachable nodes in an unweighted graph. It is also suitable for exploring a graph layer by layer.
//   • Idea: BFS systematically explores a graph level by level, starting from a source node, ensuring all nodes at a given distance are visited before moving to the next distance level. It operates in O(N + M) time for N vertices and M edges.
//   • Invariants: All nodes currently in the queue are at the same or adjacent distance level from the source.; The 'used' array accurately reflects all nodes that have been added to the queue for processing.
//   • Tips: Always use a queue to maintain the order of nodes to visit.; Utilize a 'visited' array or set to prevent revisiting nodes and infinite loops.
//   • Pitfalls: Does not find shortest paths in weighted graphs unless weights are 0 or 1 (use Dijkstra for general weighted graphs).; Forgetting to mark nodes as visited can lead to incorrect results or TLE.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[][] highestPeak(int[][] isWater) {
        int m = isWater.length, n = isWater[0].length;
        int[][] height = new int[m][n];
        boolean[][] visited = new boolean[m][n];
        Queue<int[]> queue = new LinkedList<>();

        // Initialize the queue with all water cells and mark them as visited
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isWater[i][j] == 1) {
                    queue.offer(new int[]{i, j});
                    visited[i][j] = true;
                }
            }
        }

        // Directions for adjacent cells (up, down, left, right)
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Perform BFS from all water cells simultaneously
        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int x = cell[0], y = cell[1];

            for (int[] dir : directions) {
                int newX = x + dir[0], newY = y + dir[1];

                // Check if the new cell is within bounds and not visited
                if (newX >= 0 && newX < m && newY >= 0 && newY < n && !visited[newX][newY]) {
                    height[newX][newY] = height[x][y] + 1; // Set height based on the current cell
                    visited[newX][newY] = true; // Mark as visited
                    queue.offer(new int[]{newX, newY}); // Add to the queue for further processing
                }
            }
        }

        return height;          
    }
}
