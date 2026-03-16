// Source: https://leetcode.com/problems/find-the-grid-of-region-average/   |   Difficulty: Medium
//
// Problem Description:
// You are given m x n grid image which represents a grayscale image, where image[i][j] represents a pixel with intensity in the range [0..255]. You are also given a non-negative integer threshold.
//
// Two pixels are adjacent if they share an edge.
//
// A region is a 3 x 3 subgrid where the absolute difference in intensity between any two adjacent pixels is less than or equal to threshold.
//
// All pixels in a region belong to that region, note that a pixel can belong to multiple regions.
//
// You need to calculate a m x n grid result, where result[i][j] is the average intensity of the regions to which image[i][j] belongs, rounded down to the nearest integer. If image[i][j] belongs to multiple regions, result[i][j] is the average of the rounded-down average intensities of these regions, rounded down to the nearest integer. If image[i][j] does not belong to any region, result[i][j] is equal to image[i][j].
//
// Return the grid result.
//
// Example:
// Input: image = [[5,6,7,10],[8,9,10,10],[11,12,13,10]], threshold = 3
//
// Output: [[9,9,9,9],[9,9,9,9],[9,9,9,9]]
//
// Explanation:
//
//
//
// There are two regions as illustrated above. The average intensity of the first region is 9, while the average intensity of the second region is 9.67 which is rounded down to 9. The average intensity of both of the regions is (9 + 9) / 2 = 9. As all the pixels belong to either region 1, region 2, or both of them, the intensity of every pixel in the result is 9.
//
// Please note that the rounded-down values are used when calculating the average of multiple regions, hence the calculation is done using 9 as the average intensity of region 2, not 9.67.
//
// Constraints:
// 3 <= n, m <= 500
// 	0 <= image[i][j] <= 255
// 	0 <= threshold <= 255
//
// Helpful references (internal KB):
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
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
int** resultGrid(int** image, int imageSize, int* imageColSize, int threshold, int* returnSize, int** returnColumnSizes) {
    int m = imageSize;
    int n = imageColSize[0];
    int** result = (int**)malloc(m * sizeof(int*));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
    }

    int regionCount[m][n];
    int regionSum[m][n];
    memset(regionCount, 0, sizeof(regionCount));
    memset(regionSum, 0, sizeof(regionSum));

    for (int i = 0; i <= m - 3; i++) {
        for (int j = 0; j <= n - 3; j++) {
            int validRegion = 1;
            for (int x = i; x < i + 3 && validRegion; x++) {
                for (int y = j; y < j + 3 && validRegion; y++) {
                    if (x > i && abs(image[x][y] - image[x - 1][y]) > threshold) {
                        validRegion = 0;
                    }
                    if (y > j && abs(image[x][y] - image[x][y - 1]) > threshold) {
                        validRegion = 0;
                    }
                }
            }
            if (validRegion) {
                int sum = 0;
                for (int x = i; x < i + 3; x++) {
                    for (int y = j; y < j + 3; y++) {
                        sum += image[x][y];
                    }
                }
                int avg = sum / 9;
                for (int x = i; x < i + 3; x++) {
                    for (int y = j; y < j + 3; y++) {
                        regionSum[x][y] += avg;
                        regionCount[x][y]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (regionCount[i][j] > 0) {
                result[i][j] = regionSum[i][j] / regionCount[i][j];
            } else {
                result[i][j] = image[i][j];
            }
        }
    }
    *returnSize = m;
    return result;
}
