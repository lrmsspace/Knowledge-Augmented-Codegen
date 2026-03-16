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
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        const int MOD = 1e9 + 7;
        vector<vector<long long>> dp(n, vector<long long>(n, -1));
        vector<vector<long long>> count(n, vector<long long>(n, 0));
        
        dp[n-1][n-1] = 0;
        count[n-1][n-1] = 1;
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (board[i][j] == 'X' || (i == n - 1 && j == n - 1)) continue;
                
                long long maxScore = -1;
                long long ways = 0;
                
                // Check down
                if (i + 1 < n && dp[i + 1][j] != -1) {
                    if (dp[i + 1][j] > maxScore) {
                        maxScore = dp[i + 1][j];
                        ways = count[i + 1][j];
                    } else if (dp[i + 1][j] == maxScore) {
                        ways = (ways + count[i + 1][j]) % MOD;
                    }
                }
                
                // Check right
                if (j + 1 < n && dp[i][j + 1] != -1) {
                    if (dp[i][j + 1] > maxScore) {
                        maxScore = dp[i][j + 1];
                        ways = count[i][j + 1];
                    } else if (dp[i][j + 1] == maxScore) {
                        ways = (ways + count[i][j + 1]) % MOD;
                    }
                }
                
                // Check down-right
                if (i + 1 < n && j + 1 < n && dp[i + 1][j + 1] != -1) {
                    if (dp[i + 1][j + 1] > maxScore) {
                        maxScore = dp[i + 1][j + 1];
                        ways = count[i + 1][j + 1];
                    } else if (dp[i + 1][j + 1] == maxScore) {
                        ways = (ways + count[i + 1][j + 1]) % MOD;
                    }
                }
                
                if (maxScore == -1) {
                    dp[i][j] = -1;
                    count[i][j] = 0;
                } else {
                    dp[i][j] = maxScore + (board[i][j] >= '0' && board[i][j] <= '9' ? board[i][j] - '0' : 0);
                    count[i][j] = ways;
                }
            }
        }
        
        return {dp[0][0] == -1 ? 0 : (int)dp[0][0], (int)count[0][0]};
        
    }
};
