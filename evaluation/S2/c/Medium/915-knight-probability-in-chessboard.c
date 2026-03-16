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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double knightProbability(int n, int k, int row, int column) {
    // Define the possible moves of a knight in chess
    int moves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
    // Create a 3D array to store the probabilities
    double dp[k + 1][n][n];
    
    // Initialize the dp array for k = 0 (base case)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[0][i][j] = 1.0; // Probability of being on the board at step 0 is 1
        }
    }
    
    // Fill the dp array for each step from 1 to k
    for (int step = 1; step <= k; step++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[step][i][j] = 0.0; // Initialize probability for this cell at this step
                for (int m = 0; m < 8; m++) {
                    int prevRow = i - moves[m][0];
                    int prevCol = j - moves[m][1];
                    if (prevRow >= 0 && prevRow < n && prevCol >= 0 && prevCol < n) {
                        dp[step][i][j] += dp[step - 1][prevRow][prevCol] / 8.0;
                    }
                }
            }
        }
    }
    
    // Return the probability of being on the board after k moves starting from (row, column)
    return dp[k][row][column];      
}
