// Source: https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer matrix grid and an integer k.
//
// Return the number of submatrices that contain the top-left element of the grid, and have a sum less than or equal to k.
//
// Example:
// Input: grid = [[7,6,3],[6,6,1]], k = 18
// Output: 4
// Explanation: There are only 4 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 18.
//
// Constraints:
// m == grid.length 
// 	n == grid[i].length
// 	1 <= n, m <= 1000 
// 	0 <= grid[i][j] <= 1000
// 	1 <= k <= 109
//

class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        // Compute prefix sums
        vector<vector<int>> prefixSum(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefixSum[i][j] = grid[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }

        int count = 0;

        // Iterate over all possible bottom-right corners
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int submatrixSum = prefixSum[i][j]; // Sum of submatrix from (0,0) to (i-1,j-1)
                if (submatrixSum <= k) {
                    count++;
                }
            }
        }

        return count;           
    }
};
