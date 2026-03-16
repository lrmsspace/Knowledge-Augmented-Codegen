// Source: https://leetcode.com/problems/number-of-paths-with-max-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.
//
// You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
//
// Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.
//
// In case there is no path, return [0, 0].
//
// Example:
// Input: board = ["E23","2X2","12S"]
// Output: [7,1]
//
// Constraints:
// 2 <= board.length == board[i].length <= 100
//

class Solution {
    public int[] pathsWithMaxScore(List<String> board) {
        int n = board.size();
        int m = board.get(0).length();
        int mod = 1_000_000_007;

        int[][] dp = new int[n][m];
        int[][] count = new int[n][m];
        count[n - 1][m - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (board.get(i).charAt(j) == 'X' || (i == n - 1 && j == m - 1)) {
                    continue;
                }

                int maxScore = -1;
                int ways = 0;

                // Up
                if (i + 1 < n && count[i + 1][j] > 0) {
                    if (dp[i + 1][j] > maxScore) {
                        maxScore = dp[i + 1][j];
                        ways = count[i + 1][j];
                    } else if (dp[i + 1][j] == maxScore) {
                        ways = (ways + count[i + 1][j]) % mod;
                    }
                }

                // Left
                if (j + 1 < m && count[i][j + 1] > 0) {
                    if (dp[i][j + 1] > maxScore) {
                        maxScore = dp[i][j + 1];
                        ways = count[i][j + 1];
                    } else if (dp[i][j + 1] == maxScore) {
                        ways = (ways + count[i][j + 1]) % mod;
                    }
                }

                // Diagonal
                if (i + 1 < n && j + 1 < m && count[i + 1][j + 1] > 0) {
                    if (dp[i + 1][j + 1] > maxScore) {
                        maxScore = dp[i + 1][j + 1];
                        ways = count[i + 1][j + 1];
                    } else if (dp[i + 1][j + 1] == maxScore) {
                        ways = (ways + count[i + 1][j + 1]) % mod;
                    }
                }         
                if (ways > 0) {
                    count[i][j] = ways;
                    dp[i][j] = maxScore + (board.get(i).charAt(j) == 'E' ? 0 : board.get(i).charAt(j) - '0');
                }
                          
            }
        }
        return new int[]{dp[0][0], count[0][0]};
    }
}
