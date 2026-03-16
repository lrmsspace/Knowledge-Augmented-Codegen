// Source: https://leetcode.com/problems/number-of-music-playlists/   |   Difficulty: Hard
//
// Problem Description:
// Your music player contains n different songs. You want to listen to goal songs (not necessarily different) during your trip. To avoid boredom, you will create a playlist so that:
//
//
// 	Every song is played at least once.
// 	A song can only be played again only if k other songs have been played.
//
//
// Given n, goal, and k, return the number of possible playlists that you can create. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, goal = 3, k = 1
// Output: 6
// Explanation: There are 6 possible playlists: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], and [3, 2, 1].
//
// Constraints:
// 0 <= k < n <= goal <= 100
//

/**
 * @param {number} n
 * @param {number} goal
 * @param {number} k
 * @return {number}
 */
var numMusicPlaylists = function(n, goal, k) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: goal + 1 }, () => new Array(n + 1).fill(0));
    dp[0][0] = 1;
    for (let i = 1; i <= goal; i++) {
        for (let j = 1; j <= Math.min(i, n); j++) {
            dp[i][j] = (dp[i - 1][j - 1] * (n - (j - 1)) + dp[i - 1][j] * Math.max(j - k, 0)) % MOD;
        }
    }
    return dp[goal][n];    
};
