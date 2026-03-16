// Source: https://leetcode.com/problems/diagonal-traverse/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,4,7,5,3,6,8,9]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	-105 <= mat[i][j] <= 105
//

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return {};

        int m = mat.size();
        int n = mat[0].size();
        vector<int> result;
        result.reserve(m * n);

        for (int d = 0; d < m + n - 1; ++d) {
            if (d % 2 == 0) {
                // Traverse upwards
                int r = min(d, m - 1);
                int c = d - r;
                while (r >= 0 && c < n) {
                    result.push_back(mat[r][c]);
                    --r;
                    ++c;
                }
            } else {
                // Traverse downwards
                int c = min(d, n - 1);
                int r = d - c;
                while (c >= 0 && r < m) {
                    result.push_back(mat[r][c]);
                    ++r;
                    --c;
                }
            }
        }

        return result;          
    }
};
