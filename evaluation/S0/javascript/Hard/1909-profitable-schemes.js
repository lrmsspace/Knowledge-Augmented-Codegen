// Source: https://leetcode.com/problems/profitable-schemes/   |   Difficulty: Hard
//
// Problem Description:
// There is a group of n members, and a list of various crimes they could commit. The ith crime generates a profit[i] and requires group[i] members to participate in it. If a member participates in one crime, that member can't participate in another crime.
//
// Let's call a profitable scheme any subset of these crimes that generates at least minProfit profit, and the total number of members participating in that subset of crimes is at most n.
//
// Return the number of schemes that can be chosen. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
// Output: 2
// Explanation: To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
// In total, there are 2 schemes.
//
// Constraints:
// 1 <= n <= 100
// 	0 <= minProfit <= 100
// 	1 <= group.length <= 100
// 	1 <= group[i] <= 100
// 	profit.length == group.length
// 	0 <= profit[i] <= 100
//

/**
 * @param {number} n
 * @param {number} minProfit
 * @param {number[]} group
 * @param {number[]} profit
 * @return {number}
 */
var profitableSchemes = function(n, minProfit, group, profit) {
    const MOD = 1e9 + 7;
    const dp = Array.from({ length: n + 1 }, () => new Array(minProfit + 1).fill(0));
    dp[0][0] = 1;

    for (let i = 0; i < group.length; i++) {
        const members = group[i];
        const gain = profit[i];
        for (let j = n; j >= members; j--) {    
            for (let k = minProfit; k >= 0; k--) {
                const newProfit = Math.min(minProfit, k + gain);
                dp[j][newProfit] = (dp[j][newProfit] + dp[j - members][k]) % MOD;
            }
        }
    }
    let totalSchemes = 0;
    for (let j = 0; j <= n; j++) {
        totalSchemes = (totalSchemes + dp[j][minProfit]) % MOD;
    }
    return totalSchemes;    
};
