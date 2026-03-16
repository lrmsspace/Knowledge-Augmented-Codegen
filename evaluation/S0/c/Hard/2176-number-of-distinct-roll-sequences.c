// Source: https://leetcode.com/problems/number-of-distinct-roll-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n. You roll a fair 6-sided dice n times. Determine the total number of distinct sequences of rolls possible such that the following conditions are satisfied:
//
//
// 	The greatest common divisor of any adjacent values in the sequence is equal to 1.
// 	There is at least a gap of 2 rolls between equal valued rolls. More formally, if the value of the ith roll is equal to the value of the jth roll, then abs(i - j) > 2.
//
//
// Return the total number of distinct sequences possible. Since the answer may be very large, return it modulo 109 + 7.
//
// Two sequences are considered distinct if at least one element is different.
//
// Example:
// Input: n = 4
// Output: 184
// Explanation: Some of the possible sequences are (1, 2, 3, 4), (6, 1, 2, 3), (1, 2, 3, 1), etc.
// Some invalid sequences are (1, 2, 1, 3), (1, 2, 3, 6).
// (1, 2, 1, 3) is invalid since the first and third roll have an equal value and abs(1 - 3) = 2 (i and j are 1-indexed).
// (1, 2, 3, 6) is invalid since the greatest common divisor of 3 and 6 = 3.
// There are a total of 184 distinct sequences possible, so we return 184.
//
// Constraints:
// 1 <= n <= 104
//

int distinctSequences(int n) {
    const int MOD = 1000000007;
    /* adjacency list for valid next dice rolls */
    const int adj[6][3] = {
        {1, 3, 5},    /* from 1 to 2,4,6 */
        {0, 2, 4},    /* from 2 to 1,3,5 */
        {1, 3, 5},    /* from 3 to 2,4,6 */
        {0, 2, 4},    /* from 4 to 1,3,5 */
        {1, 3, 5},    /* from 5 to 2,4,6 */
        {0, 2, 4}     /* from 6 to 1,3,5 */
    };

    /* dp[i][j][k]: number of sequences of length i+1 ending with j+1,
       where the last occurrence of k+1 is at position i-2 or earlier
       (k == -1 means no restriction) */
    int ***dp = (int***)malloc(n * sizeof(int**));
    for (int i = 0; i < n; ++i) {
        dp[i] = (int**)malloc(6 * sizeof(int*));
        for (int j = 0; j < 6; ++j) {
            dp[i][j] = (int*)calloc(7, sizeof(int));
        }
    }

    /* base case: length 1 sequences */
    for (int j = 0; j < 6; ++j) {
        dp[0][j][6] = 1; /* no restriction */
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 6; ++j) { /* current last roll */
            for (int k = 0; k < 7; ++k) { /* previous last roll restriction */
                for (int next : adj[j]) { /* valid next rolls */
                    if (next != k) { /* satisfy the gap condition */
                        dp[i][next][j] = (dp[i][next][j] + dp[i - 1][j][k]) % MOD;
                    }
                }
            }
        }
    }
    int result = 0;
    for (int j = 0; j < 6; ++j) {
        for (int k = 0; k < 7; ++k) {
            result = (result + dp[n - 1][j][k]) % MOD;
        }
    }
    /* free allocated memory */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
    return result;
}
