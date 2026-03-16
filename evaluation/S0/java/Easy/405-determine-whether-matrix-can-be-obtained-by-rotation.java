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

class Solution {
    public boolean findRotation(int[][] mat, int[][] target) {
        int n = mat.length;

        for (int rotation = 0; rotation < 4; rotation++) {
            if (areMatricesEqual(mat, target)) {
                return true;
            }
            mat = rotateMatrixBy90Degrees(mat, n);
        }

        return false;           
    }
}
