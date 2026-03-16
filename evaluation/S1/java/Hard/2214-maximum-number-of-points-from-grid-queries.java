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
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Range Minimum Query (array, ds, divide-and-conquer)
//   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
//   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
//   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
//   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] maxPoints(int[][] grid, int[] queries) {
        int m = grid.length, n = grid[0].length, k = queries.length;
        int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int[][] queryWithIndex = new int[k][2];
        for (int i = 0; i < k; i++) {
            queryWithIndex[i][0] = queries[i];
            queryWithIndex[i][1] = i;
        }
        Arrays.sort(queryWithIndex, (a, b) -> Integer.compare(a[0], b[0]));

        boolean[][] visited = new boolean[m][n];
        PriorityQueue<int[]> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        minHeap.offer(new int[]{grid[0][0], 0, 0});
        visited[0][0] = true;

        int[] answer = new int[k];
        int points = 0;
        int queryIdx = 0;

        while (queryIdx < k) {
            int currentQueryValue = queryWithIndex[queryIdx][0];

            while (!minHeap.isEmpty() && minHeap.peek()[0] < currentQueryValue) {
                int[] cell = minHeap.poll();
                points++;

                for (int[] dir : dirs) {
                    int newRow = cell[1] + dir[0];
                    int newCol = cell[2] + dir[1];

                    if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && !visited[newRow][newCol]) {
                        visited[newRow][newCol] = true;
                        minHeap.offer(new int[]{grid[newRow][newCol], newRow, newCol});
                    }
                }
            }

            while (queryIdx < k && queryWithIndex[queryIdx][0] == currentQueryValue) {
                answer[queryWithIndex[queryIdx][1]] = points;
                queryIdx++;
            }
        }

        return answer;          
    }
}
