// Source: https://leetcode.com/problems/count-numbers-with-non-decreasing-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, l and r, represented as strings, and an integer b. Return the count of integers in the inclusive range [l, r] whose digits are in non-decreasing order when represented in base b.
//
// An integer is considered to have non-decreasing digits if, when read from left to right (from the most significant digit to the least significant digit), each digit is greater than or equal to the previous one.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: l = "23", r = "28", b = 8
//
// Output: 3
//
// Explanation:
//
//
// 	The numbers from 23 to 28 in base 8 are: 27, 30, 31, 32, 33, and 34.
// 	Out of these, 27, 33, and 34 have non-decreasing digits. Hence, the output is 3.
//
// Constraints:
// 1 <= l.length <= r.length <= 100
// 	2 <= b <= 10
// 	l and r consist only of digits.
// 	The value represented by l is less than or equal to the value represented by r.
// 	l and r do not contain leading zeros.
//

/**
 * @param {string} l
 * @param {string} r
 * @param {number} b
 * @return {number}
 */
var countNumbers = function(l, r, b) {
    const MOD = 1e9 + 7;

    function modInverse(a, mod) {
        let m0 = mod, t, q;
        let x0 = 0, x1 = 1;
        if (mod === 1) return 0;
        while (a > 1) {
            q = Math.floor(a / mod);
            t = mod;
            mod = a % mod; a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }
    function nCr(n, r) {
        if (r > n || r < 0) return 0;
        return (factorial[n] * invFactorial[r] % MOD) * invFactorial[n - r] % MOD;
    }
    const maxLen = Math.max(l.length, r.length);
    const factorial = Array(maxLen + b).fill(1);
    for (let i = 1; i < factorial.length; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    const invFactorial = Array(maxLen + b).fill(1);
    invFactorial[factorial.length - 1] = modInverse(factorial[factorial.length - 1], MOD);
    for (let i = factorial.length - 2; i >= 0; i--) {
        invFactorial[i] = (invFactorial[i + 1] * (i + 1)) % MOD;
    }
    function countUpTo(numStr) {
        const digits = numStr.split('').map(ch => parseInt(ch, 10));
        const n = digits.length;
        let totalCount = 0;
        for (let len = 1; len < n; len++) {
            totalCount = (totalCount + nCr(len + b - 1, b - 1)) % MOD;
        }
        const memo = {};
        function dfs(pos, prevDigit, isLimit) {
            if (pos === n) return 1;    
            const key = `${pos},${prevDigit},${isLimit}`;
            if (memo.hasOwnProperty(key)) return memo[key];
            let limit = isLimit ? digits[pos] : b - 1;
            let count = 0;  
            for (let d = prevDigit; d <= limit; d++) {
                count = (count + dfs(pos + 1, d, isLimit && (d === limit))) % MOD;
            }
            memo[key] = count;
            return count;
        }
        totalCount = (totalCount + dfs(0, 0, true)) % MOD;
        return totalCount;
    }
    const countR = countUpTo(r);
    const countL = countUpTo((BigInt(l) - BigInt(1)).toString());
    return (countR - countL + MOD) % MOD;
};
