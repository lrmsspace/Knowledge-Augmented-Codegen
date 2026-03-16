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

/**
 * @param {number[][]} hats
 * @return {number}
 */
var numberWays = function(hats) {
    const MOD = 1e9 + 7;
    const n = hats.length;
    const hatToPeople = Array.from({ length: 41 }, () => []);
    for (let i = 0; i < n; i++) {
        for (const hat of hats[i]) {
            hatToPeople[hat].push(i);
        }
    }
    const dp = new Array(1 << n).fill(0);
    dp[0] = 1;
    for (let hat = 1; hat <= 40; hat++) {
        const people = hatToPeople[hat];
        if (people.length === 0) continue;
        const newDp = dp.slice();
        for (let mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] === 0) continue;
            for (const person of people) {
                if ((mask & (1 << person)) === 0) {
                    newDp[mask | (1 << person)] = (newDp[mask | (1 << person)] + dp[mask]) % MOD;
                }
            }
        }
        dp.splice(0, dp.length, ...newDp);
    }
    return dp[(1 << n) - 1];
};
