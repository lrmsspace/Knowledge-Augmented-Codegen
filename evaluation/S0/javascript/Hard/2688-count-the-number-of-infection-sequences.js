// Source: https://leetcode.com/problems/count-the-number-of-infection-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an array sick sorted in increasing order, representing positions of infected people in a line of n people.
//
// At each step, one uninfected person adjacent to an infected person gets infected. This process continues until everyone is infected.
//
// An infection sequence is the order in which uninfected people become infected, excluding those initially infected.
//
// Return the number of different infection sequences possible, modulo 109+7.
//
// Example:
// Input: n = 5, sick = [0,4]
//
// Output: 4
//
// Explanation:
//
// There is a total of 6 different sequences overall.
//
//
// 	Valid infection sequences are [1,2,3], [1,3,2], [3,2,1] and [3,1,2].
// 	[2,3,1] and [2,1,3] are not valid infection sequences because the person at index 2 cannot be infected at the first step.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= sick.length <= n - 1
// 	0 <= sick[i] <= n - 1
// 	sick is sorted in increasing order.
//

/**
 * @param {number} n
 * @param {number[]} sick
 * @return {number}
 */
var numberOfSequence = function(n, sick) {
    const mod = 1e9 + 7;
    const m = sick.length;
    const dp = Array(m + 1).fill(0);
    dp[0] = 1;
    for (let i = 1; i <= m; i++) {
        dp[i] = (dp[i - 1] * i) % mod;
    }
    let result = 1;
    for (let i = 1; i < m; i++) {
        const gap = sick[i] - sick[i - 1] - 1;
        if (gap > 0) {
            result = (result * dp[gap]) % mod;
        }
    }
    const leftGap = sick[0];
    const rightGap = n - 1 - sick[m - 1];
    if (leftGap > 0) {
        result = (result * dp[leftGap]) % mod;
    }
    if (rightGap > 0) {
        result = (result * dp[rightGap]) % mod;
    }
    return result;  
};
