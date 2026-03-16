// Source: https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/   |   Difficulty: Hard
//
// Problem Description:
// There are n people and 40 types of hats labeled from 1 to 40.
//
// Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.
//
// Return the number of ways that n people can wear different hats from each other.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: hats = [[3,4],[4,5],[5]]
// Output: 1
// Explanation: There is only one way to choose hats given the conditions. 
// First person choose hat 3, Second person choose hat 4 and last one hat 5.
//
// Constraints:
// n == hats.length
// 	1 <= n <= 10
// 	1 <= hats[i].length <= 40
// 	1 <= hats[i][j] <= 40
// 	hats[i] contains a list of unique integers.
//

int numberWays(int** hats, int hatsSize, int* hatsColSize) {
    const int MOD = 1000000007;
    int dp[1 << 10];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    for (int hat = 1; hat <= 40; ++hat) {
        int new_dp[1 << 10];
        memcpy(new_dp, dp, sizeof(dp));

        for (int person = 0; person < hatsSize; ++person) {
            // Check if this person likes the current hat
            int likes_hat = 0;
            for (int k = 0; k < hatsColSize[person]; ++k) {
                if (hats[person][k] == hat) {
                    likes_hat = 1;
                    break;
                }
            }
            if (!likes_hat) continue;
            for (int mask = 0; mask < (1 << hatsSize); ++mask) {
                if ((mask & (1 << person)) == 0) {
                    int new_mask = mask | (1 << person);
                    new_dp[new_mask] = (new_dp[new_mask] + dp[mask]) % MOD;
                }
            }
        }
        memcpy(dp, new_dp, sizeof(dp));
    }
    return dp[(1 << hatsSize) - 1];
}
