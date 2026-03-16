// Source: https://leetcode.com/problems/count-anagrams/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s containing one or more words. Every consecutive pair of words is separated by a single space ' '.
//
// A string t is an anagram of string s if the ith word of t is a permutation of the ith word of s.
//
//
// 	For example, "acb dfe" is an anagram of "abc def", but "def cab" and "adc bef" are not.
//
//
// Return the number of distinct anagrams of s. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "too hot"
// Output: 18
// Explanation: Some of the anagrams of the given string are "too hot", "oot hot", "oto toh", "too toh", and "too oht".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters and spaces ' '.
// 	There is single space between consecutive words.
//

/**
 * @param {string} s
 * @return {number}
 */
var countAnagrams = function(s) {
    const mod = 1e9 + 7;
    const words = s.split(' ');
    const factorial = [1];
    for (let i = 1; i <= 100000; i++) {
        factorial[i] = (factorial[i - 1] * i) % mod;
    }
    const inverseFactorial = [1];
    for (let i = 1; i <= 100000; i++) {
        inverseFactorial[i] = modInverse(factorial[i], mod);
    }
    const modInverse = (a, m) => {
        let m0 = m, t, q;
        if (m === 1) return 0;
        while (a > 1) {
            q = Math.floor(a / m);
            t = m;
            m = a % m;
            a = t;
            t = inverseFactorial[q];
            inverseFactorial[q] = inverseFactorial[a];
            inverseFactorial[a] = t;
        }
        if (inverseFactorial[a] < 0) inverseFactorial[a] += m0;
        return inverseFactorial[a];
    }
    let result = 1;
    for (const word of words) {
        const count = new Array(26).fill(0);
        for (const char of word) {
            count[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
        }
        let wordAnagrams = factorial[word.length];
        for (const c of count) {
            if (c > 1) {
                wordAnagrams = (wordAnagrams * inverseFactorial[c]) % mod;
            }
        }
        result = (result * wordAnagrams) % mod;
    }
    return result;
};
