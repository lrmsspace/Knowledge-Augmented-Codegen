// Source: https://leetcode.com/problems/find-all-groups-of-farmland/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix land where a 0 represents a hectare of forested land and a 1 represents a hectare of farmland.
//
// To keep the land organized, there are designated rectangular areas of hectares that consist entirely of farmland. These rectangular areas are called groups. No two groups are adjacent, meaning farmland in one group is not four-directionally adjacent to another farmland in a different group.
//
// land can be represented by a coordinate system where the top left corner of land is (0, 0) and the bottom right corner of land is (m-1, n-1). Find the coordinates of the top left and bottom right corner of each group of farmland. A group of farmland with a top left corner at (r1, c1) and a bottom right corner at (r2, c2) is represented by the 4-length array [r1, c1, r2, c2].
//
// Return a 2D array containing the 4-length arrays described above for each group of farmland in land. If there are no groups of farmland, return an empty array. You may return the answer in any order.
//
// Example:
// Input: land = [[1,0,0],[0,1,1],[0,1,1]]
// Output: [[0,0,0,0],[1,1,2,2]]
// Explanation:
// The first group has a top left corner at land[0][0] and a bottom right corner at land[0][0].
// The second group has a top left corner at land[1][1] and a bottom right corner at land[2][2].
//
// Constraints:
// m == land.length
// 	n == land[i].length
// 	1 <= m, n <= 300
// 	land consists of only 0's and 1's.
// 	Groups of farmland are rectangular in shape.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findFarmland(int** land, int landSize, int* landColSize, int* returnSize, int** returnColumnSizes) {
    int maxGroups = landSize * (*landColSize) / 2; // Maximum possible groups
    int** result = (int**)malloc(maxGroups * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxGroups * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < landSize; i++) {
        for (int j = 0; j < landColSize[0]; j++) {
            if (land[i][j] == 1) {
                int r1 = i, c1 = j;
                int r2 = i, c2 = j;

                // Find the bottom-right corner of the farmland group
                while (r2 + 1 < landSize && land[r2 + 1][j] == 1) {
                    r2++;
                }
                while (c2 + 1 < landColSize[0] && land[i][c2 + 1] == 1) {
                    c2++;
                }

                // Mark the farmland as visited
                for (int x = r1; x <= r2; x++) {
                    for (int y = c1; y <= c2; y++) {
                        land[x][y] = 0;
                    }
                }

                // Store the result
                result[*returnSize] = (int*)malloc(4 * sizeof(int));
                result[*returnSize][0] = r1;
                result[*returnSize][1] = c1;
                result[*returnSize][2] = r2;
                result[*returnSize][3] = c2;
                (*returnColumnSizes)[*returnSize] = 4;
                (*returnSize)++;
            }
        }
    }

    return result;      
}
