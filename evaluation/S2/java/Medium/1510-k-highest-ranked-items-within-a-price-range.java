// Source: https://leetcode.com/problems/k-highest-ranked-items-within-a-price-range/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n that represents a map of the items in a shop. The integers in the grid represent the following:
//
//
// 	0 represents a wall that you cannot pass through.
// 	1 represents an empty cell that you can freely move to and from.
// 	All other positive integers represent the price of an item in that cell. You may also freely move to and from these item cells.
//
//
// It takes 1 step to travel between adjacent grid cells.
//
// You are also given integer arrays pricing and start where pricing = [low, high] and start = [row, col] indicates that you start at the position (row, col) and are interested only in items with a price in the range of [low, high] (inclusive). You are further given an integer k.
//
// You are interested in the positions of the k highest-ranked items whose prices are within the given price range. The rank is determined by the first of these criteria that is different:
//
//
// 	Distance, defined as the length of the shortest path from the start (shorter distance has a higher rank).
// 	Price (lower price has a higher rank, but it must be in the price range).
// 	The row number (smaller row number has a higher rank).
// 	The column number (smaller column number has a higher rank).
//
//
// Return the k highest-ranked items within the price range sorted by their rank (highest to lowest). If there are fewer than k reachable items within the price range, return all of them.
//
// Example:
// Input: grid = [[1,2,0,1],[1,3,0,1],[0,2,5,1]], pricing = [2,5], start = [0,0], k = 3
// Output: [[0,1],[1,1],[2,1]]
// Explanation: You start at (0,0).
// With a price range of [2,5], we can take items from (0,1), (1,1), (2,1) and (2,2).
// The ranks of these items are:
// - (0,1) with distance 1
// - (1,1) with distance 2
// - (2,1) with distance 3
// - (2,2) with distance 4
// Thus, the 3 highest ranked items in the price range are (0,1), (1,1), and (2,1).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= grid[i][j] <= 105
// 	pricing.length == 2
// 	2 <= low <= high <= 105
// 	start.length == 2
// 	0 <= row <= m - 1
// 	0 <= col <= n - 1
// 	grid[row][col] > 0
// 	1 <= k <= m * n
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - 0-1 BFS (graph, queue, 01-bfs, bfs)
//   • When to use: Use when finding shortest paths in a graph where edge weights are restricted to only 0 or 1. It efficiently determines minimum distances from a source to all reachable nodes, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds shortest paths from a single source in a graph where all edge weights are either 0 or 1. It achieves this in O(V + E) time complexity by using a deque to prioritize 0-weight edges.
//   • Invariants: All nodes in the deque have a distance value less than or equal to any node not yet processed.; Nodes added to the front of the deque (0-weight edges) always have a distance equal to the node they came from.
//   • Tips: Use a deque to maintain order: 0-weight edges go to front, 1-weight edges to back.; Initialize distances to infinity and source distance to 0.
//   • Pitfalls: Forgetting to update distances for 0-weight edges before adding to deque front.; Incorrectly handling visited states, leading to TLE or incorrect paths.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<List<Integer>> highestRankedKItems(int[][] grid, int[] pricing, int[] start, int k) {
        int m = grid.length, n = grid[0].length;
        int low = pricing[0], high = pricing[1];
        int startRow = start[0], startCol = start[1];

        List<List<Integer>> result = new ArrayList<>();
        boolean[][] visited = new boolean[m][n];
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{startRow, startCol, 0}); // {row, col, distance}
        visited[startRow][startCol] = true;

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int row = current[0], col = current[1], distance = current[2];

            if (grid[row][col] >= low && grid[row][col] <= high) {
                result.add(Arrays.asList(row, col));
            }

            if (result.size() == k) {
                break;
            }

            for (int[] dir : new int[][]{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];

                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] != 0 && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    queue.offer(new int[]{newRow, newCol, distance + 1});
                }
            }
        }

        result.sort((a, b) -> {
            int distA = Math.abs(a.get(0) - startRow) + Math.abs(a.get(1) - startCol);
            int distB = Math.abs(b.get(0) - startRow) + Math.abs(b.get(1) - startCol);
            if (distA != distB) return Integer.compare(distA, distB);
            if (grid[a.get(0)][a.get(1)] != grid[b.get(0)][b.get(1)]) {
                return Integer.compare(grid[a.get(0)][a.get(1)], grid[b.get(0)][b.get(1)]);
            }
            if (!a.get(0).equals(b.get(0))) return Integer.compare(a.get(0), b.get(0));      
            return Integer.compare(a.get(1), b.get(1));
        });   
    }
}
