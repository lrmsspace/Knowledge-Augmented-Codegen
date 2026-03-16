// Source: https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/   |   Difficulty: Medium
//
// Problem Description:
// Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.
//
// Example:
// Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
// Output: 2
// Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 300
// 	0 <= mat[i][j] <= 104
// 	0 <= threshold <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Sqrt Tree (array, tree, recursion, simulation)
//   • When to use: Use for efficient range queries on an array, achieving very low query complexity by leveraging a hierarchical block decomposition and specific structural properties like power-of-two block sizes.
//   • Idea: A Sqrt Tree is a hierarchical data structure designed for answering range queries on an array, achieving O(log log n) or better query time by recursively decomposing the array into blocks and layers.
//   • Invariants: Each layer of the Sqrt Tree consists of segments of equal length.; All blocks within a given layer have an equal, power-of-two size.
//   • Tips: Pad the input array with dummy elements to ensure its size is a power of two for simplified block calculations.; Ensure all block sizes on each layer are powers of two to enable efficient binary representation tricks for queries.
//   • Pitfalls: Incorrectly calculating block boundaries or segment sizes, leading to off-by-one errors or out-of-bounds access.; Overlooking the memory overhead associated with storing precomputed values for all blocks across multiple layers.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean canFindSquare(int[][] prefixSum, int sideLength, int threshold) {
        int m = prefixSum.length - 1;
        int n = prefixSum[0].length - 1;

        for (int i = sideLength; i <= m; i++) {
            for (int j = sideLength; j <= n; j++) {
                int total = prefixSum[i][j] - prefixSum[i - sideLength][j] - prefixSum[i][j - sideLength] + prefixSum[i - sideLength][j - sideLength];
                if (total <= threshold) {
                    return true;
                }
            }
        }
        return false;
    }
    public int maxSideLength(int[][] mat, int threshold) {
        int m = mat.length, n = mat[0].length;
        int[][] prefixSum = new int[m + 1][n + 1];

        // Compute prefix sum matrix
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefixSum[i][j] = mat[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }

        int left = 0, right = Math.min(m, n);
        int maxSideLength = 0;

        // Binary search for the maximum side length
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canFindSquare(prefixSum, mid, threshold)) {
                maxSideLength = mid; // Update max side length
                left = mid + 1; // Try for a larger size
            } else {
                right = mid - 1; // Try for a smaller size
            }
        }

        return maxSideLength;           
    }
}
