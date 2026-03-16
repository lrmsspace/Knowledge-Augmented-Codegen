// Source: https://leetcode.com/problems/largest-magic-square/   |   Difficulty: Medium
//
// Problem Description:
// A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both diagonal sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic square.
//
// Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found within this grid.
//
// Example:
// Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
// Output: 3
// Explanation: The largest magic square has a size of 3.
// Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
// - Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
// - Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
// - Diagonal sums: 5+4+3 = 6+4+2 = 12
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j] <= 106
//
// Helpful references (internal KB):
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Prefix sums for rows and columns
        vector<vector<int>> rowPrefix(m, vector<int>(n + 1, 0));
        vector<vector<int>> colPrefix(n, vector<int>(m + 1, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowPrefix[i][j + 1] = rowPrefix[i][j] + grid[i][j];
                colPrefix[j][i + 1] = colPrefix[j][i] + grid[i][j];
            }
        }

        auto getRowSum = [&](int r, int c1, int c2) {
            return rowPrefix[r][c2 + 1] - rowPrefix[r][c1];
        };

        auto getColSum = [&](int c, int r1, int r2) {
            return colPrefix[c][r2 + 1] - colPrefix[c][r1];
        };

        int maxSize = min(m, n);
        for (int size = maxSize; size >= 1; --size) {
            for (int r = 0; r <= m - size; ++r) {
                for (int c = 0; c <= n - size; ++c) {
                    int targetSum = getRowSum(r, c, c + size - 1);
                    bool isMagic = true;

                    // Check rows
                    for (int i = r; i < r + size; ++i) {
                        if (getRowSum(i, c, c + size - 1) != targetSum) {
                            isMagic = false;
                            break;
                        }
                    }
                    if (!isMagic) continue;

                    // Check columns
                    for (int j = c; j < c + size; ++j) {
                        if (getColSum(j, r, r + size - 1) != targetSum) {
                            isMagic = false;
                            break;
                        }
                    }
                    if (!isMagic) continue;

                    // Check main diagonal
                    int diagSum1 = 0;
                    for (int i = 0; i < size; ++i) {
                        diagSum1 += grid[r + i][c + i];
                    }
                    if (diagSum1 != targetSum) continue;

                    // Check anti diagonal
                    int diagSum2 = 0;
                    for (int i = 0; i < size; ++i) {
                        diagSum2 += grid[r + i][c + size - 1 - i];
                    }
                    if (diagSum2 != targetSum) continue;

                    return size; // Found the largest magic square
                }
            }
        }
        return 1; // At least 1x1 magic square exists
    }
};
