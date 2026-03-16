// Source: https://leetcode.com/problems/count-stepping-numbers-in-range/   |   Difficulty: Hard
//
// Problem Description:
// Given two positive integers low and high represented as strings, find the count of stepping numbers in the inclusive range [low, high].
//
// A stepping number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
//
// Return an integer denoting the count of stepping numbers in the inclusive range [low, high]. 
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note: A stepping number should not have a leading zero.
//
// Example:
// Input: low = "1", high = "11"
// Output: 10
// Explanation: The stepping numbers in the range [1,11] are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10. There are a total of 10 stepping numbers in the range. Hence, the output is 10.
//
// Constraints:
// 1 <= int(low) <= int(high) < 10100
// 	1 <= low.length, high.length <= 100
// 	low and high consist of only digits.
// 	low and high don't have any leading zeros.
//

/**
 * @param {string} low
 * @param {string} high
 * @return {number}
 */
var countSteppingNumbers = function(low, high) {
    const mod = 1e9 + 7;
    const countUpTo = (numStr) => {
        const n = numStr.length;
        const memo = Array.from({ length: n + 1 }, () => new Array(10).fill(-1));
        const dfs = (pos, prevDigit, tight) => {
            if (pos === n) {
                return 1;
            }
            if (memo[pos][prevDigit] !== -1 && !tight) {
                return memo[pos][prevDigit];
            }
            let limit = tight ? parseInt(numStr[pos]) : 9;
            let count = 0;
            for (let digit = 0; digit <= limit; digit++) {
                if (prevDigit === -1 || Math.abs(digit - prevDigit) === 1) {
                    count = (count + dfs(pos + 1, digit, tight && digit === limit)) % mod;
                }
            }
            if (!tight) {
                memo[pos][prevDigit] = count;
            }
            return count;
        }
        return dfs(0, -1, true);
    }
    const countLow = countUpTo(low);
    const countHigh = countUpTo(high);
    return (countHigh - countLow + mod) % mod;
        
};
