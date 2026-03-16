// Source: https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D matrix of size m x n, consisting of non-negative integers. You are also given an integer k.
//
// The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j] where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).
//
// Find the kth largest value (1-indexed) of all the coordinates of matrix.
//
// Example:
// Input: matrix = [[5,2],[1,6]], k = 1
// Output: 7
// Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 1000
// 	0 <= matrix[i][j] <= 106
// 	1 <= k <= m * n
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Sqrt Tree (array, tree, recursion)
//   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
//   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
//   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
//   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
//   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int kthLargestValue(int[][] matrix, int k) {
        int m = matrix.length, n = matrix[0].length;
        int[] xorValues = new int[m * n];
        int idx = 0;

        // Compute the XOR values for each coordinate (a, b)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int xorValue = matrix[i][j];
                if (i > 0) xorValue ^= matrix[i - 1][j];
                if (j > 0) xorValue ^= matrix[i][j - 1];
                if (i > 0 && j > 0) xorValue ^= matrix[i - 1][j - 1];
                matrix[i][j] = xorValue; // Update the original matrix with the XOR value
                xorValues[idx++] = xorValue; // Store the XOR value in the array
            }
        }

        // Sort the XOR values in descending order
        Arrays.sort(xorValues);
        return xorValues[xorValues.length - k]; // Return the k-th largest value            
    }
}
