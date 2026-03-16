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
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
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
            for (int j = 0; j < n; j++) {
                dist[i][j] = Integer.MAX_VALUE;
            }
        }
        dist[0][0] = 1;

        MinQueue[] rowQueues = new MinQueue[m];
        MinQueue[] colQueues = new MinQueue[n];
        for (int i = 0; i < m; i++) {
            rowQueues[i] = new MinQueue();
            rowQueues[i].push(new int[]{0, 1});
        }
        for (int j = 0; j < n; j++) {
            colQueues[j] = new MinQueue();
            colQueues[j].push(new int[]{0, 1});
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                int minRowDist = rowQueues[i].min()[1];
                int minColDist = colQueues[j].min()[1];
                int currDist = Math.min(minRowDist, minColDist);
                if (currDist == Integer.MAX_VALUE) {
                    continue;
                }
                dist[i][j] = currDist + 1;

                int rightLimit = Math.min(n - 1, j + grid[i][j]);
                if (rightLimit > j) {
                    rowQueues[i].push(new int[]{rightLimit, dist[i][j]});
                }

                int downLimit = Math.min(m - 1, i + grid[i][j]);
                if (downLimit > i) {
                    colQueues[j].push(new int[]{downLimit, dist[i][j]});
                }
            }
            rowQueues[i].clear();
        }

        return dist[m - 1][n - 1] == Integer.MAX_VALUE ? -1 : dist[m - 1][n - 1];           
    }
}
