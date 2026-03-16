// Source: https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​.
//
// A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus sum:
//
// Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.
//
// Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct values, return all of them.
//
// Example:
// Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
// Output: [228,216,211]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 20 + 3 + 200 + 5 = 228
// - Red: 200 + 2 + 10 + 4 = 216
// - Green: 5 + 200 + 4 + 2 = 211
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j] <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getBiggestThree(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int m = gridSize, n = gridColSize[0];
    int maxRhombusSize = (m < n ? m : n) / 2;
    int rhombusSums[2500];
    int rhombusSumsCount = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int size = 0; size <= maxRhombusSize; size++) {
                if (i - size < 0 || i + size >= m || j - size < 0 || j + size >= n) {
                    break;
                }

                int sum = 0;
                if (size == 0) {
                    sum = grid[i][j];
                } else {
                    for (int k = 0; k < size; k++) {
                        sum += grid[i - k][j + k]; // Top-right edge
                        sum += grid[i + k][j + k]; // Bottom-right edge
                        sum += grid[i + k][j - k]; // Bottom-left edge
                        sum += grid[i - k][j - k]; // Top-left edge
                    }
                    sum += grid[i + size][j]; // Bottom vertex
                    sum += grid[i - size][j]; // Top vertex
                }

                // Check for uniqueness
                int isUnique = 1;
                for (int x = 0; x < rhombusSumsCount; x++) {
                    if (rhombusSums[x] == sum) {
                        isUnique = 0;
                        break;
                    }
                }
                if (isUnique) {
                    rhombusSums[rhombusSumsCount++] = sum;
                }
            }
        }
    }

    // Sort the sums in descending order
    qsort(rhombusSums, rhombusSumsCount, sizeof(int), [](const void* a, const void* b) {
        return (*(int*)b - *(int*)a);
    });
    // Prepare the result
    int resultSize = (rhombusSumsCount < 3) ? rhombusSumsCount : 3;
    int* result = (int*)malloc(resultSize * sizeof(int));
    for (int i = 0; i < resultSize; i++) {
        result[i] = rhombusSums[i];
    }
    *returnSize = resultSize;
    return result;
}
