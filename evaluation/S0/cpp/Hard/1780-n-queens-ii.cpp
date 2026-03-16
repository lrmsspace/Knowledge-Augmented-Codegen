// Source: https://leetcode.com/problems/n-queens-ii/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return the number of distinct solutions to the n-queens puzzle.
//
// Example:
// Input: n = 4
// Output: 2
// Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
//
// Constraints:
// 1 <= n <= 9
//

class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        vector<int> queens(n, -1);
        vector<bool> columns(n, false);
        vector<bool> diagonals1(2 * n - 1, false);
        vector<bool> diagonals2(2 * n - 1, false);
        
        function<void(int)> backtrack = [&](int row) {
            if (row == n) {
                count++;
                return;
            }
            for (int col = 0; col < n; col++) {
                if (columns[col] || diagonals1[row + col] || diagonals2[row - col + n - 1]) {
                    continue;
                }
                queens[row] = col;
                columns[col] = true;
                diagonals1[row + col] = true;
                diagonals2[row - col + n - 1] = true;
                
                backtrack(row + 1);
                
                queens[row] = -1;
                columns[col] = false;
                diagonals1[row + col] = false;
                diagonals2[row - col + n - 1] = false;
            }
        };
        
        backtrack(0);
        return count;           
    }
};
