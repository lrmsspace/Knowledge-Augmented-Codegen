// Source: https://leetcode.com/problems/count-fertile-pyramids-in-a-land/   |   Difficulty: Hard
//
// Problem Description:
// A farmer has a rectangular grid of land with m rows and n columns that can be divided into unit cells. Each cell is either fertile (represented by a 1) or barren (represented by a 0). All cells outside the grid are considered barren.
//
// A pyramidal plot of land can be defined as a set of cells with the following criteria:
//
//
// 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
// 	The apex of a pyramid is the topmost cell of the pyramid. The height of a pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r <= i <= r + h - 1 and c - (i - r) <= j <= c + (i - r).
//
//
// An inverse pyramidal plot of land can be defined as a set of cells with similar criteria:
//
//
// 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
// 	The apex of an inverse pyramid is the bottommost cell of the inverse pyramid. The height of an inverse pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r - h + 1 <= i <= r and c - (r - i) <= j <= c + (r - i).
//
//
// Some examples of valid and invalid pyramidal (and inverse pyramidal) plots are shown below. Black cells indicate fertile cells.
//
// Given a 0-indexed m x n binary matrix grid representing the farmland, return the total number of pyramidal and inverse pyramidal plots that can be found in grid.
//
// Example:
// Input: grid = [[0,1,1,0],[1,1,1,1]]
// Output: 2
// Explanation: The 2 possible pyramidal plots are shown in blue and red respectively.
// There are no inverse pyramidal plots in this grid. 
// Hence total number of pyramidal and inverse pyramidal plots is 2 + 0 = 2.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
//

class Solution {
public:
    int countPyramids(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int total = 0;

        // Count normal pyramids
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    if (i == m - 1) {
                        dp[i][j] = 1;
                    } else {
                        int left = (j > 0) ? dp[i + 1][j - 1] : 0;
                        int right = (j < n - 1) ? dp[i + 1][j + 1] : 0;
                        dp[i][j] = 1 + min(left, right);
                    }
                    total += dp[i][j] - 1; // height - 1 gives number of pyramids
                }
            }
        }

        // Count inverse pyramids
        dp.assign(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    if (i == 0) {
                        dp[i][j] = 1;
                    } else {
                        int left = (j > 0) ? dp[i - 1][j - 1] : 0;
                        int right = (j < n - 1) ? dp[i - 1][j + 1] : 0;
                        dp[i][j] = 1 + min(left, right);
                    }
                    total += dp[i][j] - 1; // height - 1 gives number of inverse pyramids
                }
            }
        }

        return total;           
    }
};
