// Source: https://leetcode.com/problems/jump-game-vii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:
//
//
// 	i + minJump <= j <= min(i + maxJump, s.length - 1), and
// 	s[j] == '0'.
//
//
// Return true if you can reach index s.length - 1 in s, or false otherwise.
//
// Example:
// Input: s = "011010", minJump = 2, maxJump = 3
// Output: true
// Explanation:
// In the first step, move from index 0 to index 3. 
// In the second step, move from index 3 to index 5.
//
// Constraints:
// 2 <= s.length <= 105
// 	s[i] is either '0' or '1'.
// 	s[0] == '0'
// 	1 <= minJump <= maxJump < s.length
//

/**
 * @param {string} s
 * @param {number} minJump
 * @param {number} maxJump
 * @return {boolean}
 */
var canReach = function(s, minJump, maxJump) {
    const n = s.length;
    const dp = Array(n).fill(false);
    dp[0] = true;
    let farthest = 0;
    for (let i = 1; i < n; i++) {
        if (s[i] === '0') {
            const start = Math.max(farthest + 1, i - maxJump);
            const end = i - minJump;
            for (let j = start; j <= end; j++) {
                if (dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        if (dp[i]) {
            farthest = i;
        }
    }
    return dp[n - 1];   
};
