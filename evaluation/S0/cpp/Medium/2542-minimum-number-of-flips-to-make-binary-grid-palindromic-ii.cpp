// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid.
//
// A row or column is considered palindromic if its values read the same forward and backward.
//
// You can flip any number of cells in grid from 0 to 1, or from 1 to 0.
//
// Return the minimum number of cells that need to be flipped to make all rows and columns palindromic, and the total number of 1's in grid divisible by 4.
//
// Example:
// Input: grid = [[1,0,0],[0,1,0],[0,0,1]]
//
// Output: 3
//
// Explanation:
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m * n <= 2 * 105
// 	0 <= grid[i][j] <= 1
//

class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int totalFlips = 0;

        for (int layer = 0; layer < (m + 1) / 2; ++layer) {
            for (int col = 0; col < (n + 1) / 2; ++col) {
                vector<pair<int, int>> positions;
                positions.emplace_back(layer, col);
                if (col != n - col - 1)
                    positions.emplace_back(layer, n - col - 1);
                if (layer != m - layer - 1)
                    positions.emplace_back(m - layer - 1, col);
                if (layer != m - layer - 1 && col != n - col - 1)
                    positions.emplace_back(m - layer - 1, n - col - 1);

                int countOnes = 0;
                for (const auto& pos : positions) {
                    countOnes += grid[pos.first][pos.second];
                }

                int flipsForThisGroup = min(countOnes, static_cast<int>(positions.size()) - countOnes);
                totalFlips += flipsForThisGroup;
            }
        }

        return totalFlips;          
    }
};
