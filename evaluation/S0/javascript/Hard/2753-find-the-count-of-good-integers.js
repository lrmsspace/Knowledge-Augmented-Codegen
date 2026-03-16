// Source: https://leetcode.com/problems/find-the-count-of-good-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// An integer is called good if its digits can be rearranged to form a k-palindromic integer. For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a k-palindromic integer.
//
// Return the count of good integers containing n digits.
//
// Note that any integer must not have leading zeros, neither before nor after rearrangement. For example, 1010 cannot be rearranged to form 101.
//
// Example:
// Input: n = 3, k = 5
//
// Output: 27
//
// Explanation:
//
// Some of the good integers are:
//
//
// 	551 because it can be rearranged to form 515.
// 	525 because it is already k-palindromic.
//
// Constraints:
// 1 <= n <= 10
// 	1 <= k <= 9
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var countGoodIntegers = function(n, k) {
    const MOD = 1e9 + 7;
    const factorial = Array(n + 1).fill(1);
    for (let i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    const invFactorial = Array(n + 1).fill(1);
    invFactorial[n] = modInverse(factorial[n], MOD);
    for (let i = n - 1; i >= 0; i--) {
        invFactorial[i] = (invFactorial[i + 1] * (i + 1)) % MOD;
    }
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
        return (factorial[n] * ((invFactorial[r] * invFactorial[n - r]) % MOD)) % MOD;
    }
    let result = 0;
    for (let oddCount = 0; oddCount <= Math.min(n, 9); oddCount += 2) {
        if ((n % 2 === 0 && oddCount > 0) || (n % 2 === 1 && oddCount !== 1)) continue;
        const evenCount = n - oddCount;
        const waysToChooseDigits = (oddCount === 0 ? 1 : nCr(9, oddCount)) * nCr(10 - oddCount, evenCount);
        let arrangements = factorial[n];
        const countMap = {};
        for (let i = 0; i < oddCount; i++) {
            countMap[1] = (countMap[1] || 0) + 1;
        }
        for (let i = 0; i < evenCount; i++) {
            countMap[0] = (countMap[0] || 0) + 1;
        }
        for (const count of Object.values(countMap)) {
            arrangements = (arrangements * invFactorial[count]) % MOD;
        }
        result = (result + (waysToChooseDigits * arrangements) % MOD) % MOD;
    }
    return result;
};
