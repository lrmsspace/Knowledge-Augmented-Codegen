// Source: https://leetcode.com/problems/matrix-block-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given a m x n matrix mat and an integer k, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for:
//
//
// 	i - k <= r <= i + k,
// 	j - k <= c <= j + k, and
// 	(r, c) is a valid position in the matrix.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[12,21,16],[27,45,33],[24,39,28]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n, k <= 100
// 	1 <= mat[i][j] <= 100
//

class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> prefixSum(m + 1, vector<int>(n + 1, 0));
        
        // Compute prefix sum
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefixSum[i][j] = mat[i - 1][j - 1] 
                                  + prefixSum[i - 1][j] 
                                  + prefixSum[i][j - 1] 
                                  - prefixSum[i - 1][j - 1];
            }
        }
        
        vector<vector<int>> answer(m, vector<int>(n, 0));
        
        // Calculate block sum for each element
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int r1 = max(0, i - k);
                int c1 = max(0, j - k);
                int r2 = min(m - 1, i + k);
                int c2 = min(n - 1, j + k);
                
                answer[i][j] = prefixSum[r2 + 1][c2 + 1] 
                               - prefixSum[r1][c2 + 1] 
                               - prefixSum[r2 + 1][c1] 
                               + prefixSum[r1][c1];
            }
        }
        
        return answer;          
    }
};
