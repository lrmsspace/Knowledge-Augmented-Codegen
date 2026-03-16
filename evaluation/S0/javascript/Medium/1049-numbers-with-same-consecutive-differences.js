// Source: https://leetcode.com/problems/numbers-with-same-consecutive-differences/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, return an array of all the integers of length n where the difference between every two consecutive digits is k. You may return the answer in any order.
//
// Note that the integers should not have leading zeros. Integers as 02 and 043 are not allowed.
//
// Example:
// Input: n = 3, k = 7
// Output: [181,292,707,818,929]
// Explanation: Note that 070 is not a valid number, because it has leading zeroes.
//
// Constraints:
// 2 <= n <= 9
// 	0 <= k <= 9
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number[]}
 */
var numsSameConsecDiff = function(n, k) {
    const result = [];
    const dfs = (num, length) => {
        if (length === n) {
            result.push(num);
            return;
        }
        const lastDigit = num % 10;
        const nextDigits = new Set();
        nextDigits.add(lastDigit + k);
        nextDigits.add(lastDigit - k);
        for (const nextDigit of nextDigits) {
            if (nextDigit >= 0 && nextDigit <= 9) {
                dfs(num * 10 + nextDigit, length + 1);
            }
        }
    }
    for (let i = 1; i <= 9; i++) {
        dfs(i, 1);
    }
    return result;  

                
};
