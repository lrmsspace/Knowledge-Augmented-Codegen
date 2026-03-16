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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> rowSum(m, vector<int>(n + 1)), colSum(m + 1, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowSum[i][j + 1] = rowSum[i][j] + grid[i][j];
                colSum[i + 1][j] = colSum[i][j] + grid[i][j];
            }
        }

        for (int k = min(m, n); k > 0; --k) {
            for (int i = 0; i <= m - k; ++i) {
                for (int j = 0; j <= n - k; ++j) {
                    int sum = rowSum[i][j + k] - rowSum[i][j];
                    bool isMagicSquare = true;
                    for (int x = i; x < i + k && isMagicSquare; ++x) {
                        if (rowSum[x][j + k] - rowSum[x][j] != sum) {
                            isMagicSquare = false;
                        }
                    }
                    for (int y = j; y < j + k && isMagicSquare; ++y) {
                        if (colSum[i + k][y] - colSum[i][y] != sum) {
                            isMagicSquare = false;
                        }
                    }
                    int diag1 = 0, diag2 = 0;
                    for (int d = 0; d < k && isMagicSquare; ++d) {
                        diag1 += grid[i + d][j + d];
                        diag2 += grid[i + d][j + k - 1 - d];
                    }
                    if (isMagicSquare && diag1 == sum && diag2 == sum) {
                        return k;
                    }
                }
            }
        }

        return 1;           
    }
};
