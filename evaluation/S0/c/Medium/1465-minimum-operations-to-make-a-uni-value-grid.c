// Source: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.
//
// A uni-value grid is a grid where all the elements of it are equal.
//
// Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.
//
// Example:
// Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
// Explanation: We can make every element equal to 4 by doing the following: 
// - Add x to 2 once.
// - Subtract x from 6 once.
// - Subtract x from 8 twice.
// A total of 4 operations were used.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= x, grid[i][j] <= 104
//

int minOperations(int** grid, int gridSize, int* gridColSize, int x) {
    int totalElements = gridSize * (*gridColSize);
    int* flatGrid = (int*)malloc(totalElements * sizeof(int));
    int index = 0;
    
    // Flatten the 2D grid into a 1D array
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            flatGrid[index++] = grid[i][j];
        }
    }
    
    // Check if all elements have the same remainder when divided by x
    int remainder = flatGrid[0] % x;
    for (int i = 1; i < totalElements; i++) {
        if (flatGrid[i] % x != remainder) {
            free(flatGrid);
            return -1;
        }
    }
    
    // Sort the flattened array to find the median
    qsort(flatGrid, totalElements, sizeof(int), (int (*)(const void*, const void*))strcmp);
    
    int median = flatGrid[totalElements / 2];
    int operations = 0;
    
    // Calculate the total number of operations needed to make all elements equal to the median
    for (int i = 0; i < totalElements; i++) {
        operations += abs(flatGrid[i] - median) / x;
    }
    
    free(flatGrid);
    return operations;      
}
