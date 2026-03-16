// Source: https://leetcode.com/problems/maximal-rectangle/   |   Difficulty: Hard
//
// Problem Description:
// Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
//
// Example:
// Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 6
// Explanation: The maximal rectangle is shown in the above picture.
//
// Constraints:
// rows == matrix.length
// 	cols == matrix[i].length
// 	1 <= row, cols <= 200
// 	matrix[i][j] is '0' or '1'.
//

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize == NULL || matrixColSize[0] == 0) {
        return 0;
    }

    int maxArea = 0;
    int cols = matrixColSize[0];
    int* heights = (int*)calloc(cols, sizeof(int));
    if (!heights) return 0;

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == '1') {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }

        // Calculate max area in histogram
        int* stack = (int*)malloc((cols + 1) * sizeof(int));
        if (!stack) {
            free(heights);
            return 0;
        }
        int top = -1;
        for (int j = 0; j <= cols; ++j) {
            int h = (j == cols) ? 0 : heights[j];
            while (top != -1 && h < heights[stack[top]]) {
                int height = heights[stack[top--]];
                int width = (top == -1) ? j : j - stack[top] - 1;
                int area = height * width;
                if (area > maxArea) {
                    maxArea = area;
                }
            }
            stack[++top] = j;
        }
        free(stack);
    }

    free(heights);
    return maxArea;     
}
