// Source: https://leetcode.com/problems/surrounded-regions/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
//
//
// 	Connect: A cell is connected to adjacent cells horizontally or vertically.
// 	Region: To form a region connect every 'O' cell.
// 	Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
//
//
// To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.
//
// Example:
// Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
//
// Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
//
// Explanation:
//
// In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 200
// 	board[i][j] is 'X' or 'O'.
//

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        int m = board.size();
        int n = board[0].size();

        // DFS to mark 'O's connected to the border
        function<void(int, int)> dfs = [&](int x, int y) {
            if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] != 'O') return;
            board[x][y] = 'E'; // Mark as escaped
            dfs(x + 1, y);
            dfs(x - 1, y);
            dfs(x, y + 1);
            dfs(x, y - 1);
        };

        // Start DFS from the borders
        for (int i = 0; i < m; ++i) {
            if (board[i][0] == 'O') dfs(i, 0);
            if (board[i][n - 1] == 'O') dfs(i, n - 1);
        }
        for (int j = 0; j < n; ++j) {
            if (board[0][j] == 'O') dfs(0, j);
            if (board[m - 1][j] == 'O') dfs(m - 1, j);
        }

        // Flip captured 'O's to 'X' and revert escaped 'E's back to 'O'
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X'; // Captured
                } else if (board[i][j] == 'E') {
                    board[i][j] = 'O'; // Revert back
                }
            }
        }               
    }
};
