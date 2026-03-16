// Source: https://leetcode.com/problems/find-the-closest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
//
// The closest is defined as the absolute difference minimized between two integers.
//
// Example:
// Input: n = "123"
// Output: "121"
//
// Constraints:
// 1 <= n.length <= 18
// 	n consists of only digits.
// 	n does not have leading zeros.
// 	n is representing an integer in the range [1, 1018 - 1].
//

/**
 * @param {string} n
 * @return {string}
 */
var nearestPalindromic = function(n) {
    const num = BigInt(n);
    const candidates = new Set();
    const prefix = n.slice(0, Math.ceil(n.length / 2));
    const prefixNum = BigInt(prefix);
    for (let i = -1n; i <= 1n; i++) {
        const newPrefix = (prefixNum + i).toString();
        const palindrome = newPrefix + newPrefix.split('').reverse().slice(n.length % 2).join('');
        candidates.add(palindrome);
    }
    candidates.add((10n ** BigInt(n.length - 1) - 1n).toString());
    candidates.add((10n ** BigInt(n.length) + 1n).toString());
    let closest = null;
    for (const candidate of candidates) {
        if (candidate === n) continue;
        const candidateNum = BigInt(candidate);
        const diff = candidateNum > num ? candidateNum - num : num - candidateNum;
        if (closest === null || diff < closest.diff || (diff === closest.diff && candidateNum < BigInt(closest.value))) {
            closest = { value: candidate, diff };
        }
    }
    return closest.value;   
};
