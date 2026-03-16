// Source: https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/   |   Difficulty: Hard
//
// Problem Description:
// Given a matrix and a target, return the number of non-empty submatrices that sum to target.
//
// A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
//
// Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
//
// Example:
// Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
// Output: 4
// Explanation: The four 1x1 submatrices that only contain 0.
//
// Constraints:
// 1 <= matrix.length <= 100
// 	1 <= matrix[0].length <= 100
// 	-1000 <= matrix[i][j] <= 1000
// 	-10^8 <= target <= 10^8
//

int numSubmatrixSumTarget(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int result = 0;

    for (int top = 0; top < rows; ++top) {
        int *colSums = (int*)calloc(cols, sizeof(int));
        for (int bottom = top; bottom < rows; ++bottom) {
            for (int c = 0; c < cols; ++c) {
                colSums[c] += matrix[bottom][c];
            }

            /* Find the number of subarrays in colSums that sum to target */
            int currSum = 0;
            int *prefixSums = (int*)calloc(2001, sizeof(int)); // Offset by 1000
            prefixSums[1000] = 1; // Base case: sum of 0
            for (int c = 0; c < cols; ++c) {
                currSum += colSums[c];
                if (currSum - target + 1000 >= 0 && currSum - target + 1000 <= 2000) {
                    result += prefixSums[currSum - target + 1000];
                }
                if (currSum + 1000 >= 0 && currSum + 1000 <= 2000) {
                    prefixSums[currSum + 1000]++;
                }
            }
            free(prefixSums);
        }
        free(colSums);
    }

    return result;      
}
