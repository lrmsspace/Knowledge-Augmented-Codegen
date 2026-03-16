// Source: https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers n, m, k. A good array arr of size n is defined as follows:
//
//
// 	Each element in arr is in the inclusive range [1, m].
// 	Exactly k indices i (where 1 <= i < n) satisfy the condition arr[i - 1] == arr[i].
//
//
// Return the number of good arrays that can be formed.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, m = 2, k = 1
//
// Output: 4
//
// Explanation:
//
//
// 	There are 4 good arrays. They are [1, 1, 2], [1, 2, 2], [2, 1, 1] and [2, 2, 1].
// 	Hence, the answer is 4.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= m <= 105
// 	0 <= k <= n - 1
//

int countGoodArrays(int n, int m, int k) {
    const int MOD = 1000000007;

    /* dp[i][j]: number of arrays of length i with j adjacent matches */
    long long *dp_prev = (long long*)calloc(k + 1, sizeof(long long));
    long long *dp_curr = (long long*)calloc(k + 1, sizeof(long long));
    if (!dp_prev || !dp_curr) {
        free(dp_prev); free(dp_curr);
        return 0;
    }

    dp_prev[0] = m; /* base case: length 1, 0 matches */

    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            /* Case 1: arr[i-1] == arr[i-2], contributes to a match */
            if (j > 0) {
                dp_curr[j] = (dp_prev[j - 1] * 1) % MOD;
            } else {
                dp_curr[j] = 0;
            }
            /* Case 2: arr[i-1] != arr[i-2], does not contribute to a match */
            dp_curr[j] = (dp_curr[j] + dp_prev[j] * (m - 1)) % MOD;
        }
        /* Swap dp arrays for next iteration */
        long long *temp = dp_prev;
        dp_prev = dp_curr;
        dp_curr = temp;
    }

    int result = (int)dp_prev[k];
    free(dp_prev);
    free(dp_curr);
    return result;      
}
