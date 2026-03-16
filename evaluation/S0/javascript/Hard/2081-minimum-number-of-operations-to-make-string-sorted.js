// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s (0-indexed)​​​​​​. You are asked to perform the following operation on s​​​​​​ until you get a sorted string:
//
//
// 	Find the largest index i such that 1 <= i < s.length and s[i] < s[i - 1].
// 	Find the largest index j such that i <= j < s.length and s[k] < s[i - 1] for all the possible values of k in the range [i, j] inclusive.
// 	Swap the two characters at indices i - 1​​​​ and j​​​​​.
// 	Reverse the suffix starting at index i​​​​​​.
//
//
// Return the number of operations needed to make the string sorted. Since the answer can be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "cba"
// Output: 5
// Explanation: The simulation goes as follows:
// Operation 1: i=2, j=2. Swap s[1] and s[2] to get s="cab", then reverse the suffix starting at 2. Now, s="cab".
// Operation 2: i=1, j=2. Swap s[0] and s[2] to get s="bac", then reverse the suffix starting at 1. Now, s="bca".
// Operation 3: i=2, j=2. Swap s[1] and s[2] to get s="bac", then reverse the suffix starting at 2. Now, s="bac".
// Operation 4: i=1, j=1. Swap s[0] and s[1] to get s="abc", then reverse the suffix starting at 1. Now, s="acb".
// Operation 5: i=2, j=2. Swap s[1] and s[2] to get s="abc", then reverse the suffix starting at 2. Now, s="abc".
//
// Constraints:
// 1 <= s.length <= 3000
// 	s​​​​​​ consists only of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var makeStringSorted = function(s) {
    const MOD = 1e9 + 7;
    const n = s.length;
    const count = new Array(26).fill(0);
    for (const char of s) {
        count[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    const factorial = new Array(n + 1).fill(1);
    for (let i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    const inverseFactorial = new Array(n + 1).fill(1);
    inverseFactorial[n] = modInverse(factorial[n], MOD);
    for (let i = n - 1; i >= 0; i--) {
        inverseFactorial[i] = (inverseFactorial[i + 1] * (i + 1)) % MOD;
    }
    let result = 0;
    for (let i = 0; i < n; i++) {
        const charIndex = s.charCodeAt(i) - 'a'.charCodeAt(0);
        for (let j = 0; j < charIndex; j++) {
            if (count[j] > 0) {
                count[j]--;
                let permutations = factorial[n - i - 1];
                for (let k = 0; k < 26; k++) {
                    permutations = (permutations * inverseFactorial[count[k]]) % MOD;
                }
                result = (result + permutations) % MOD;
                count[j]++;
            }
        }
        count[charIndex]--;
    }
    return result;  
};
