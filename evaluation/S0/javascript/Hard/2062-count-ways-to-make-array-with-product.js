// Source: https://leetcode.com/problems/count-ways-to-make-array-with-product/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find the number of different ways you can place positive integers into an array of size ni such that the product of the integers is ki. As the number of ways may be too large, the answer to the ith query is the number of ways modulo 109 + 7.
//
// Return an integer array answer where answer.length == queries.length, and answer[i] is the answer to the ith query.
//
// Example:
// Input: queries = [[2,6],[5,1],[73,660]]
// Output: [4,1,50734910]
// Explanation: Each query is independent.
// [2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
// [5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
// [73,660]: There are 1050734917 ways to fill an array of size 73 that multiply to 660. 1050734917 modulo 109 + 7 = 50734910.
//
// Constraints:
// 1 <= queries.length <= 104 
// 	1 <= ni, ki <= 104
//

/**
 * @param {number[][]} queries
 * @return {number[]}
 */
var waysToFillArray = function(queries) {
    const MOD = 1e9 + 7;
    const maxN = Math.max(...queries.map(q => q[0]));
    const maxK = Math.max(...queries.map(q => q[1]));
    const dp = Array.from({ length: maxN + 1 }, () => new Array(maxK + 1).fill(0));
    dp[0][1] = 1;
    for (let n = 1; n <= maxN; n++) {
        for (let k = 1; k <= maxK; k++) {
            for (let i = 1; i <= k; i++) {
                if (k % i === 0) {
                    dp[n][k] = (dp[n][k] + dp[n - 1][k / i]) % MOD;
                }
            }
        }
    }
    const results = [];
    for (const [n, k] of queries) {
        results.push(dp[n][k]);
    }
    return results; 
};
