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
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();

        for (int rotation = 0; rotation < 4; ++rotation) {
            bool match = true;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (mat[i][j] != target[i][j]) {
                        match = false;
                        break;
                    }
                }
                if (!match) break;
            }

            if (match) return true;

            // Rotate mat 90 degrees clockwise
            vector<vector<int>> rotated(n, vector<int>(n));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    rotated[j][n - 1 - i] = mat[i][j];
                }
            }
            mat = rotated;
        }

        return false;           
    }
};
