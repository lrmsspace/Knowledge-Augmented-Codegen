// Source: https://leetcode.com/problems/cyclically-rotating-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
//
// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
//
//
//
// A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:
//
// Return the matrix after applying k cyclic rotations to it.
//
// Example:
// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 50
// 	Both m and n are even integers.
// 	1 <= grid[i][j] <= 5000
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
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

int** rotateGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes){
    int m = gridSize, n = gridColSize[0];
    int** rotatedGrid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; ++i) {
        rotatedGrid[i] = (int*)malloc(n * sizeof(int));
    }
    
    // Calculate the number of layers
    int layers = (m < n ? m : n) / 2;
    
    // Rotate each layer
    for (int layer = 0; layer < layers; ++layer) {
        int top = layer, bottom = m - 1 - layer;
        int left = layer, right = n - 1 - layer;
        
        // Calculate the number of elements in the current layer
        int perimeter = 2 * (bottom - top + right - left);
        int effectiveRotations = k % perimeter;
        
        // Create a temporary array to hold the elements of the current layer
        int* temp = (int*)malloc(perimeter * sizeof(int));
        int index = 0;
        
        // Top row
        for (int j = left; j <= right; ++j) {
            temp[index++] = grid[top][j];
        }
        // Right column
        for (int i = top + 1; i <= bottom; ++i) {
            temp[index++] = grid[i][right];
        }
        // Bottom row
        for (int j = right - 1; j >= left; --j) {
            temp[index++] = grid[bottom][j];
        }
        // Left column
        for (int i = bottom - 1; i > top; --i) {
            temp[index++] = grid[i][left];
        }
        
        // Rotate the temporary array
        int* rotatedTemp = (int*)malloc(perimeter * sizeof(int));
        for (int i = 0; i < perimeter; ++i) {
            rotatedTemp[(i + effectiveRotations) % perimeter] = temp[i];
        }
        
        // Place the rotated elements back into the grid
        index = 0;
        for (int j = left; j <= right; ++j) {
            rotatedGrid[top][j] = rotatedTemp[index++];
        }
        for (int i = top + 1; i <= bottom; ++i) {
            rotatedGrid[i][right] = rotatedTemp[index++];
        }
        for (int j = right - 1; j >= left; --j) {
            rotatedGrid[bottom][j] = rotatedTemp[index++];
        }
        for (int i = bottom - 1; i > top; --i) {
            rotatedGrid[i][left] = rotatedTemp[index++];
        }
        free(temp);
        free(rotatedTemp);
    }
    
    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; ++i) {
        (*returnColumnSizes)[i] = n;
    }
    return rotatedGrid;
}
