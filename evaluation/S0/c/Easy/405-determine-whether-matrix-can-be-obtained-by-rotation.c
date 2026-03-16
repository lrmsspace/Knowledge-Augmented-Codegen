// Source: https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/   |   Difficulty: Easy
//
// Problem Description:
// Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, or false otherwise.
//
// Example:
// Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
// Output: true
// Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.
//
// Constraints:
// n == mat.length == target.length
// 	n == mat[i].length == target[i].length
// 	1 <= n <= 10
// 	mat[i][j] and target[i][j] are either 0 or 1.
//

bool findRotation(int** mat, int matSize, int* matColSize, int** target, int targetSize, int* targetColSize) {
    int n = matSize;
    for (int rotation = 0; rotation < 4; rotation++) {
        bool match = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int rotated_i = j;
                int rotated_j = n - 1 - i;
                if (mat[rotated_i][rotated_j] != target[i][j]) {
                    match = false;
                    break;
                }
            }
            if (!match) {
                break;
            }
        }
        if (match) {
            return true;
        }
        // Rotate mat 90 degrees clockwise for the next iteration
        int** newMat = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) {
            newMat[i] = (int*)malloc(n * sizeof(int));
            for (int j = 0; j < n; j++) {
                newMat[i][j] = mat[n - 1 - j][i];
            }
        }
        for (int i = 0; i < n; i++) {
            free(mat[i]);
        }
        free(mat);
        mat = newMat;
    }
    return false;       
}
