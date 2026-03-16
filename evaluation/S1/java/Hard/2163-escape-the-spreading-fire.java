// Source: https://leetcode.com/problems/escape-the-spreading-fire/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three values:
//
//
// 	0 represents grass,
// 	1 represents fire,
// 	2 represents a wall that you and fire cannot pass through.
//
//
// You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, (m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all adjacent cells that are not walls.
//
// Return the maximum number of minutes that you can stay in your initial position before moving while still safely reaching the safehouse. If this is impossible, return -1. If you can always reach the safehouse regardless of the minutes stayed, return 109.
//
// Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse.
//
// A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
// Example:
// Input: grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
// Output: 3
// Explanation: The figure above shows the scenario where you stay in the initial position for 3 minutes.
// You will still be able to safely reach the safehouse.
// Staying for more than 3 minutes will not allow you to safely reach the safehouse.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 300
// 	4 <= m * n <= 2 * 104
// 	grid[i][j] is either 0, 1, or 2.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Maximum flow - Ford-Fulkerson and Edmonds-Karp (graph, array, bfs)
//   • When to use: When needing to find the maximum possible flow from a source to a sink in a flow network. It is particularly useful for problems involving resource allocation, transportation, or matching.
//   • Idea: Ford-Fulkerson finds maximum flow by repeatedly augmenting paths in a residual graph. Edmonds-Karp uses BFS for shortest augmenting paths, ensuring O(VE^2) time complexity and termination.
//   • Invariants: The flow through any edge never exceeds its capacity.; For every vertex (except source and sink), total incoming flow equals total outgoing flow (flow conservation).
//   • Tips: Always construct a residual graph to represent remaining capacities and backward flow.; BFS ensures finding the shortest augmenting path, leading to the O(VE^2) complexity.
//   • Pitfalls: Incorrectly updating residual capacities for backward edges can lead to wrong results.; Using DFS for Ford-Fulkerson can lead to poor performance or non-termination with irrational capacities.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean canReachSafehouse(int[][] grid, int[][] fireTime, int waitTime) {
        int m = grid.length;
        int n = grid[0].length;
        if (fireTime[0][0] <= waitTime) {
            return false;
        }

        Queue<int[]> queue = new LinkedList<>();
        boolean[][] visited = new boolean[m][n];
        queue.offer(new int[]{0, 0, waitTime});
        visited[0][0] = true;

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int x = cell[0], y = cell[1], currentTime = cell[2];

            if (x == m - 1 && y == n - 1) {
                return true;
            }

            for (int[] dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                int arrivalTime = currentTime + 1;
                if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                    grid[newX][newY] != 2 &&
                    !visited[newX][newY] &&
                    arrivalTime < fireTime[newX][newY]) {
                    visited[newX][newY] = true;
                    queue.offer(new int[]{newX, newY, arrivalTime});
                }
            }
        }

        return false;
    }
    public int maximumMinutes(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        int[][] fireTime = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                fireTime[i][j] = Integer.MAX_VALUE;
            }
        }

        Queue<int[]> fireQueue = new LinkedList<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fireQueue.offer(new int[]{i, j});
                    fireTime[i][j] = 0;
                }
            }
        }

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!fireQueue.isEmpty()) {
            int[] cell = fireQueue.poll();
            int x = cell[0], y = cell[1];
            for (int[] dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                    grid[newX][newY] != 2 &&
                    fireTime[newX][newY] == Integer.MAX_VALUE) {
                    fireTime[newX][newY] = fireTime[x][y] + 1;
                    fireQueue.offer(new int[]{newX, newY});
                }
            }
        }

        int left = -1, right = (int)1e9;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (canReachSafehouse(grid, fireTime, mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return left == (int)1e9 ? (int)1e9 : left;          
    }
}
