// Source: https://leetcode.com/problems/pascals-triangle/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer numRows, return the first numRows of Pascal's triangle.
//
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
//
// Example:
// Input: numRows = 5
// Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
//
// Constraints:
// 1 <= numRows <= 30
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int** triangle = (int**)malloc(numRows * sizeof(int*));
    *returnColumnSizes = (int*)malloc(numRows * sizeof(int));
    *returnSize = numRows;

    for (int row = 0; row < numRows; row++) {
        triangle[row] = (int*)malloc((row + 1) * sizeof(int));
        (*returnColumnSizes)[row] = row + 1;

        triangle[row][0] = 1; // First element is always 1
        triangle[row][row] = 1; // Last element is always 1

        for (int col = 1; col < row; col++) {
            triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
        }
    }

    return triangle;        
}
