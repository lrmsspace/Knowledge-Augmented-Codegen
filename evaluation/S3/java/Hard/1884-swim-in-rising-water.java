// Source: https://leetcode.com/problems/swim-in-rising-water/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
//
// It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.
//
// You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
//
// Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).
//
// Example:
// Input: grid = [[0,2],[1,3]]
// Output: 3
// Explanation:
// At time 0, you are in grid location (0, 0).
// You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
// You cannot reach point (1, 1) until time 3.
// When the depth of water is 3, we can swim anywhere inside the grid.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	0 <= grid[i][j] < n2
// 	Each value grid[i][j] is unique.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when you need to find the shortest path (in terms of number of edges) from a source node to all other reachable nodes in an unweighted graph. It is also suitable for exploring a graph layer by layer.
//   • Idea: BFS systematically explores a graph level by level, starting from a source node, ensuring all nodes at a given distance are visited before moving to the next distance level. It operates in O(N + M) time for N vertices and M edges.
//   • Invariants: All nodes currently in the queue are at the same or adjacent distance level from the source.; The 'used' array accurately reflects all nodes that have been added to the queue for processing.
//   • Tips: Always use a queue to maintain the order of nodes to visit.; Utilize a 'visited' array or set to prevent revisiting nodes and infinite loops.
//   • Pitfalls: Does not find shortest paths in weighted graphs unless weights are 0 or 1 (use Dijkstra for general weighted graphs).; Forgetting to mark nodes as visited can lead to incorrect results or TLE.
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int swimInWater(int[][] grid) {
        int n = grid.length;
        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        boolean[][] used = new boolean[n][n];
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0});
        used[0][0] = true;
        int time = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] cell = queue.poll();
                int x = cell[0], y = cell[1];
                if (x == n - 1 && y == n - 1) {
                    return time;
                }
                for (int[] dir : directions) {
                    int newX = x + dir[0], newY = y + dir[1];
                    if (newX >= 0 && newX < n && newY >= 0 && newY < n
                            && !used[newX][newY] && grid[newX][newY] <= time) {
                        used[newX][newY] = true;
                        queue.offer(new int[]{newX, newY});
                    }
                }
            }
            time++;
        }
        return -1; // This line should never be reached since the problem guarantees a solution.            
    }
}
