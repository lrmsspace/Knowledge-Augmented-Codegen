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



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pathsWithMaxScore(char ** board, int boardSize, int* returnSize){
    if (!board || boardSize <= 0 || !returnSize) return NULL;

    int n = boardSize;
    int m = strlen(board[0]);
    int MOD = 1000000007;

    /* dp[i][j][0] = max score to reach (i,j)
       dp[i][j][1] = number of ways to reach (i,j) with max score */
    int ***dp = (int***)malloc(n * sizeof(int**));
    for (int i = 0; i < n; ++i) {
        dp[i] = (int**)malloc(m * sizeof(int*));
        for (int j = 0; j < m; ++j) {
            dp[i][j] = (int*)malloc(2 * sizeof(int));
            dp[i][j][0] = -1; /* max score */
            dp[i][j][1] = 0;  /* count */
        }
    }

    dp[n-1][m-1][0] = 0;
    dp[n-1][m-1][1] = 1;

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (board[i][j] == 'X' || (i == n - 1 && j == m - 1)) continue;

            int maxScore = -1;
            int count = 0;

            /* from down */
            if (i + 1 < n && dp[i + 1][j][0] != -1) {
                if (dp[i + 1][j][0] > maxScore) {
                    maxScore = dp[i + 1][j][0];
                    count = dp[i + 1][j][1];
                } else if (dp[i + 1][j][0] == maxScore) {
                    count = (count + dp[i + 1][j][1]) % MOD;
                }
            }

            /* from right */
            if (j + 1 < m && dp[i][j + 1][0] != -1) {
                if (dp[i][j + 1][0] > maxScore) {
                    maxScore = dp[i][j + 1][0];
                    count = dp[i][j + 1][1];
                } else if (dp[i][j + 1][0] == maxScore) {
                    count = (count + dp[i][j + 1][1]) % MOD;
                }
            }
            /* from down-right */
            if (i + 1 < n && j + 1 < m && dp[i + 1][j + 1][0] != -1) {
                if (dp[i + 1][j + 1][0] > maxScore) {
                    maxScore = dp[i + 1][j + 1][0];
                    count = dp[i + 1][j + 1][1];
                } else if (dp[i + 1][j + 1][0] == maxScore) {
                    count = (count + dp[i + 1][j + 1][1]) % MOD;
                }
            }
            if (maxScore != -1) {
                dp[i][j][0] = maxScore + (board[i][j] >= '0' && board[i][j] <= '9' ? (board[i][j] - '0') : 0);
                dp[i][j][1] = count;
            }
            
        }
    }

    int* result = (int*)malloc(2 * sizeof(int));
    if (dp[0][0][0] == -1) {
        result[0] = 0;
        result[1] = 0;
    } else {
        result[0] = dp[0][0][0];
        result[1] = dp[0][0][1];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);

    *returnSize = 2;
    return result;
}