// Source: https://leetcode.com/problems/count-the-number-of-ideal-arrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and maxValue, which are used to describe an ideal array.
//
// A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
//
//
// 	Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
// 	Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
//
//
// Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 2, maxValue = 5
// Output: 10
// Explanation: The following are the possible ideal arrays:
// - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
// - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
// - Arrays starting with the value 3 (1 array): [3,3]
// - Arrays starting with the value 4 (1 array): [4,4]
// - Arrays starting with the value 5 (1 array): [5,5]
// There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
//
// Constraints:
// 2 <= n <= 104
// 	1 <= maxValue <= 104
//

/**
 * @param {number} n
 * @param {number} maxValue
 * @return {number}
 */
var idealArrays = function(n, maxValue) {
    const mod = 1e9 + 7;
    const maxLength = Math.floor(Math.log2(maxValue)) + 1;
    const count = new Array(maxValue + 1).fill(0);
    for (let i = 1; i <= maxValue; i++) {
        count[i] = 1;
    }
    for (let i = 2; i <= maxValue; i++) {
        for (let j = i * 2; j <= maxValue; j += i) {
            count[j]++;
        }
    }
    const dp = Array.from({ length: maxLength }, () => new Array(maxValue + 1).fill(0));
    for (let i = 1; i <= maxValue; i++) {
        dp[1][i] = count[i];
    }
    for (let length = 2; length < maxLength; length++) {
        for (let value = 1; value <= maxValue; value++) {
            for (let multiple = value * 2; multiple <= maxValue; multiple += value) {
                dp[length][multiple] = (dp[length][multiple] + dp[length - 1][value]) % mod;
            }
        }
    }
    let result = 0;
    for (let length = 1; length < maxLength; length++) {
        if (length > n) {
            break;
        }
        const combinations = (factorial(n - 1) * modInverse(factorial(length - 1)) % mod) * modInverse(factorial(n - length)) % mod;
        for (let value = 1; value <= maxValue; value++) {
            result = (result + dp[length][value] * combinations) % mod;
        }
    }
    return result;  
};
