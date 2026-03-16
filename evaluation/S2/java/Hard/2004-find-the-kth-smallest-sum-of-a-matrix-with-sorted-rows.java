// Source: https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n matrix mat that has its rows sorted in non-decreasing order and an integer k.
//
// You are allowed to choose exactly one element from each row to form an array.
//
// Return the kth smallest array sum among all possible arrays.
//
// Example:
// Input: mat = [[1,3,11],[2,4,6]], k = 5
// Output: 7
// Explanation: Choosing one element from each row, the first k smallest sum are:
// [1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.
//
// Constraints:
// m == mat.length
// 	n == mat.length[i]
// 	1 <= m, n <= 40
// 	1 <= mat[i][j] <= 5000
// 	1 <= k <= min(200, nm)
// 	mat[i] is a non-decreasing array.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
//   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
//   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
//   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
//   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int kthSmallest(int[][] mat, int k) {
        int m = mat.length, n = mat[0].length;
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        int sum = 0;
        for (int i = 0; i < m; i++) {
            sum += mat[i][0];
        }
        pq.offer(new int[]{sum, 0, 0});
        while (k-- > 1) {
            int[] curr = pq.poll();
            int currSum = curr[0], row = curr[1], col = curr[2];
            if (col + 1 < n) {
                pq.offer(new int[]{currSum - mat[row][col] + mat[row][col + 1], row, col + 1});
            }
            if (row + 1 < m && col == 0) {
                pq.offer(new int[]{currSum - mat[row][col] + mat[row + 1][col], row + 1, col});
            }
        }
        return pq.peek()[0];            
    }
}
