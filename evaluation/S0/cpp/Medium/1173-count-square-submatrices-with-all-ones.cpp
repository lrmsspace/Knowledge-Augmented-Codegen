// Source: https://leetcode.com/problems/count-square-submatrices-with-all-ones/   |   Difficulty: Medium
//
// Problem Description:
// Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
//
// Example:
// Input: matrix =
// [
//   [0,1,1,1],
//   [1,1,1,1],
//   [0,1,1,1]
// ]
// Output: 15
// Explanation: 
// There are 10 squares of side 1.
// There are 4 squares of side 2.
// There is  1 square of side 3.
// Total number of squares = 10 + 4 + 1 = 15.
//
// Constraints:
// 1 <= arr.length <= 300
// 	1 <= arr[0].length <= 300
// 	0 <= arr[i][j] <= 1
//

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int totalSquares = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1; // First row or first column
                    } else {
                        dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                    }
                    totalSquares += dp[i][j];
                }
            }
        }

        return totalSquares;            
    }
};
