// Source: https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.
//
// Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.
//
// Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.
//
// Notice that the modulo is performed after getting the maximum product.
//
// Example:
// Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
// Output: -1
// Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	-4 <= grid[i][j] <= 4
//

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<long long>> maxProd(m, vector<long long>(n, LLONG_MIN));
        vector<vector<long long>> minProd(m, vector<long long>(n, LLONG_MAX));

        maxProd[0][0] = minProd[0][0] = grid[0][0];

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;

                long long val = grid[i][j];

                if (i > 0) {
                    long long maxFromTop = maxProd[i-1][j] * val;
                    long long minFromTop = minProd[i-1][j] * val;

                    maxProd[i][j] = max(maxProd[i][j], max(maxFromTop, minFromTop));
                    minProd[i][j] = min(minProd[i][j], min(maxFromTop, minFromTop));
                }

                if (j > 0) {
                    long long maxFromLeft = maxProd[i][j-1] * val;
                    long long minFromLeft = minProd[i][j-1] * val;

                    maxProd[i][j] = max(maxProd[i][j], max(maxFromLeft, minFromLeft));
                    minProd[i][j] = min(minProd[i][j], min(maxFromLeft, minFromLeft));
                }
            }
        }

        return maxProd[m-1][n-1] < 0 ? -1 : (maxProd[m-1][n-1] % MOD);          
    }
};
