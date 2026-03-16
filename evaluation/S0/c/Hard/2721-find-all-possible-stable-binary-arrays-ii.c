// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given 3 positive integers zero, one, and limit.
//
// A binary array arr is called stable if:
//
//
// 	The number of occurrences of 0 in arr is exactly zero.
// 	The number of occurrences of 1 in arr is exactly one.
// 	Each subarray of arr with a size greater than limit must contain both 0 and 1.
//
//
// Return the total number of stable binary arrays.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: zero = 1, one = 1, limit = 2
//
// Output: 2
//
// Explanation:
//
// The two possible stable binary arrays are [1,0] and [0,1].
//
// Constraints:
// 1 <= zero, one, limit <= 1000
//

int numberOfStableArrays(int zero, int one, int limit) {
    const int MOD = 1000000007;
    int dp[1001][1001];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i <= one; ++i) {
        for (int j = 0; j <= zero; ++j) {
            if (i == 0 && j == 0) continue;
            long long ways = 0;

            // Add a '1' if possible
            if (i > 0) {
                ways += dp[i - 1][j];
                ways %= MOD;
            }

            // Add a '0' if possible
            if (j > 0) {
                ways += dp[i][j - 1];
                ways %= MOD;
            }

            dp[i][j] = (int)ways;
        }
    }

    return dp[one][zero];       
}
