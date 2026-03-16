// Source: https://leetcode.com/problems/minimum-cost-to-merge-stones/   |   Difficulty: Hard
//
// Problem Description:
// There are n piles of stones arranged in a row. The ith pile has stones[i] stones.
//
// A move consists of merging exactly k consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these k piles.
//
// Return the minimum cost to merge all piles of stones into one pile. If it is impossible, return -1.
//
// Example:
// Input: stones = [3,2,4,1], k = 2
// Output: 20
// Explanation: We start with [3, 2, 4, 1].
// We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
// We merge [4, 1] for a cost of 5, and we are left with [5, 5].
// We merge [5, 5] for a cost of 10, and we are left with [10].
// The total cost was 20, and this is the minimum possible.
//
// Constraints:
// n == stones.length
// 	1 <= n <= 30
// 	1 <= stones[i] <= 100
// 	2 <= k <= 30
//

/**
 * @param {number[]} stones
 * @param {number} k
 * @return {number}
 */
var mergeStones = function(stones, k) {
    const n = stones.length;
    if ((n - 1) % (k - 1) !== 0) {
        return -1;
    }
    const prefixSum = new Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + stones[i];
    }

    const dp = new Array(n).fill(0).map(() => new Array(n).fill(0).map(() => new Array(k + 1).fill(Infinity)));

    for (let i = 0; i < n; i++) {
        dp[i][i][1] = 0;
    }

    for (let length = 2; length <= n; length++) {
        for (let i = 0; i <= n - length; i++) {
            let j = i + length - 1;
            for (let m = 2; m <= k; m++) {
                for (let mid = i; mid < j; mid += k - 1) {
                    dp[i][j][m] = Math.min(dp[i][j][m], dp[i][mid][1] + dp[mid + 1][j][m - 1]);
                }
            }
            dp[i][j][1] = dp[i][j][k] === Infinity ? Infinity : dp[i][j][k] + prefixSum[j + 1] - prefixSum[i];
        }
    }

    return dp[0][n - 1][1];
};
