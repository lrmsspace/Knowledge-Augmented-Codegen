// Source: https://leetcode.com/problems/largest-magic-square/   |   Difficulty: Medium
//
// Problem Description:
// A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both diagonal sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic square.
//
// Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found within this grid.
//
// Example:
// Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
// Output: 3
// Explanation: The largest magic square has a size of 3.
// Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
// - Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
// - Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
// - Diagonal sums: 5+4+3 = 6+4+2 = 12
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j] <= 106
//

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> rowPrefix(m, vector<int>(n + 1, 0));
        vector<vector<int>> colPrefix(n, vector<int>(m + 1, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowPrefix[i][j + 1] = rowPrefix[i][j] + grid[i][j];
                colPrefix[j][i + 1] = colPrefix[j][i] + grid[i][j];
            }
        }

        auto isMagicSquare = [&](int x, int y, int size) {
            int targetSum = rowPrefix[x][y + size] - rowPrefix[x][y];

            for (int i = x; i < x + size; ++i) {
                if (rowPrefix[i][y + size] - rowPrefix[i][y] != targetSum) {
                    return false;
                }
            }

            for (int j = y; j < y + size; ++j) {
                if (colPrefix[j][x + size] - colPrefix[j][x] != targetSum) {
                    return false;
                }
            }

            int diag1Sum = 0, diag2Sum = 0;
            for (int i = 0; i < size; ++i) {
                diag1Sum += grid[x + i][y + i];
                diag2Sum += grid[x + i][y + size - 1 - i];
            }

            return diag1Sum == targetSum && diag2Sum == targetSum;
        };

        int maxSize = min(m, n);
        for (int size = maxSize; size >= 1; --size) {
            for (int i = 0; i <= m - size; ++i) {
                for (int j = 0; j <= n - size; ++j) {
                    if (isMagicSquare(i, j, size)) {
                        return size;
                    }
                }
            }
        }

        return 1;           
    }
};
