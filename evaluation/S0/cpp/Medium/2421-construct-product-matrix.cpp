// Source: https://leetcode.com/problems/construct-product-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size n * m as the product matrix of grid if the following condition is met:
//
//
// 	Each element p[i][j] is calculated as the product of all elements in grid except for the element grid[i][j]. This product is then taken modulo 12345.
//
//
// Return the product matrix of grid.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: [[24,12],[8,6]]
// Explanation: p[0][0] = grid[0][1] * grid[1][0] * grid[1][1] = 2 * 3 * 4 = 24
// p[0][1] = grid[0][0] * grid[1][0] * grid[1][1] = 1 * 3 * 4 = 12
// p[1][0] = grid[0][0] * grid[0][1] * grid[1][1] = 1 * 2 * 4 = 8
// p[1][1] = grid[0][0] * grid[0][1] * grid[1][0] = 1 * 2 * 3 = 6
// So the answer is [[24,12],[8,6]].
//
// Constraints:
// 1 <= n == grid.length <= 105
// 	1 <= m == grid[i].length <= 105
// 	2 <= n * m <= 105
// 	1 <= grid[i][j] <= 109
//

class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        const int MOD = 12345;
        int n = grid.size();
        int m = grid[0].size();

        vector<long long> rowProduct(n, 1);
        vector<long long> colProduct(m, 1);

        // Calculate the product of each row and each column
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                rowProduct[i] = (rowProduct[i] * grid[i][j]) % MOD;
                colProduct[j] = (colProduct[j] * grid[i][j]) % MOD;
            }
        }

        // Construct the product matrix
        vector<vector<int>> productMatrix(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                long long val = (rowProduct[i] * colProduct[j]) % MOD;
                long long inv = modInverse(grid[i][j], MOD);
                productMatrix[i][j] = (val * inv) % MOD;
            }
        }

        return productMatrix;           
    }
};
