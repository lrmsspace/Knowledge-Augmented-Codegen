// Source: https://leetcode.com/problems/knight-probability-in-chessboard/   |   Difficulty: Medium
//
// Problem Description:
// On an n x n chessboard, a knight starts at the cell (row, column) and attempts to make exactly k moves. The rows and columns are 0-indexed, so the top-left cell is (0, 0), and the bottom-right cell is (n - 1, n - 1).
//
// A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.
//
// Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.
//
// The knight continues moving until it has made exactly k moves or has moved off the chessboard.
//
// Return the probability that the knight remains on the board after it has stopped moving.
//
// Example:
// Input: n = 3, k = 2, row = 0, column = 0
// Output: 0.06250
// Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
// From each of those positions, there are also two moves that will keep the knight on the board.
// The total probability the knight stays on the board is 0.0625.
//
// Constraints:
// 1 <= n <= 25
// 	0 <= k <= 100
// 	0 <= row, column <= n - 1
//

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        vector<vector<vector<double>>> dp(k + 1, vector<vector<double>>(n, vector<double>(n, 0.0)));
        dp[0][row][column] = 1.0;

        vector<pair<int, int>> moves = {
            {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
            {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
        };

        for (int step = 1; step <= k; ++step) {
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < n; ++c) {
                    for (const auto& move : moves) {
                        int prevR = r - move.first;
                        int prevC = c - move.second;
                        if (prevR >= 0 && prevR < n && prevC >= 0 && prevC < n) {
                            dp[step][r][c] += dp[step - 1][prevR][prevC] / 8.0;
                        }
                    }
                }
            }
        }

        double totalProbability = 0.0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                totalProbability += dp[k][r][c];
            }
        }

        return totalProbability;            
    }
};
