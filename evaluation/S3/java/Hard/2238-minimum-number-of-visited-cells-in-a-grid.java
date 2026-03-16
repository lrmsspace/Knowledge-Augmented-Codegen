// Source: https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid. Your initial position is at the top-left cell (0, 0).
//
// Starting from the cell (i, j), you can move to one of the following cells:
//
//
// 	Cells (i, k) with j < k <= grid[i][j] + j (rightward movement), or
// 	Cells (k, j) with i < k <= grid[i][j] + i (downward movement).
//
//
// Return the minimum number of cells you need to visit to reach the bottom-right cell (m - 1, n - 1). If there is no valid path, return -1.
//
// Example:
// Input: grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
// Output: 4
// Explanation: The image above shows one of the paths that visits exactly 4 cells.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= grid[i][j] < m * n
// 	grid[m - 1][n - 1] == 0
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumVisitedCells(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] dist = new int[m][n];
        for (int i = 0; i < m; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        dist[0][0] = 1;

        TreeSet<Integer>[] rows = new TreeSet[m];
        TreeSet<Integer>[] cols = new TreeSet[n];
        for (int i = 0; i < m; i++) {
            rows[i] = new TreeSet<>();
            for (int j = 0; j < n; j++) {
                rows[i].add(j);
            }
        }
        for (int j = 0; j < n; j++) {
            cols[j] = new TreeSet<>();
            for (int i = 0; i < m; i++) {
                cols[j].add(i);
            }
        }

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0});
        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            int x = cell[0], y = cell[1];
            int step = dist[x][y];

            // Move right
            int maxRight = Math.min(n - 1, y + grid[x][y]);
            Integer nextY = rows[x].ceiling(y + 1);
            while (nextY != null && nextY <= maxRight) {
                if (dist[x][nextY] > step + 1) {
                    dist[x][nextY] = step + 1;
                    queue.offer(new int[]{x, nextY});
                }
                rows[x].remove(nextY);
                nextY = rows[x].ceiling(nextY + 1);
            }

            // Move down
            int maxDown = Math.min(m - 1, x + grid[x][y]);
            Integer nextX = cols[y].ceiling(x + 1);
            while (nextX != null && nextX <= maxDown) {
                if (dist[nextX][y] > step + 1) {
                    dist[nextX][y] = step + 1;
                    queue.offer(new int[]{nextX, y});
                }
                cols[y].remove(nextX);
                nextX = cols[y].ceiling(nextX + 1);
            }
        }
        return dist[m - 1][n - 1] == Integer.MAX_VALUE ? -1 : dist[m - 1][n - 1];
    }
}
