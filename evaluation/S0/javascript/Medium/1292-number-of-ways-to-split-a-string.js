// Source: https://leetcode.com/problems/number-of-ways-to-split-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, you can split s into 3 non-empty strings s1, s2, and s3 where s1 + s2 + s3 = s.
//
// Return the number of ways s can be split such that the number of ones is the same in s1, s2, and s3. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "10101"
// Output: 4
// Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
// "1|010|1"
// "1|01|01"
// "10|10|1"
// "10|1|01"
//
// Constraints:
// 3 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

/**
 * @param {string} s
 * @return {number}
 */
var numWays = function(s) {
    const MOD = 1e9 + 7;
    const totalOnes = [...s].reduce((acc, char) => acc + (char === '1' ? 1 : 0), 0);
    if (totalOnes % 3 !== 0) return 0;
    if (totalOnes === 0) {
        const n = s.length;
        return ((n - 1) * (n - 2) / 2) % MOD;
    }
    const onesPerPart = totalOnes / 3;
    let waysFirstCut = 0;
    let waysSecondCut = 0;
    let onesCount = 0;
    for (let i = 0; i < s.length; i++) {
        if (s[i] === '1') {
            onesCount++;
        }
        if (onesCount === onesPerPart) {
            waysFirstCut++;
        } else if (onesCount === 2 * onesPerPart) {
            waysSecondCut++;
        }
    }
    return (waysFirstCut * waysSecondCut) % MOD;
};