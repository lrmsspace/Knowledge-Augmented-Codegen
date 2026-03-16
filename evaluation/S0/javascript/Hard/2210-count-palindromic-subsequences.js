// Source: https://leetcode.com/problems/count-palindromic-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.
//
// Note:
//
//
// 	A string is palindromic if it reads the same forward and backward.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "103301"
// Output: 2
// Explanation: 
// There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301". 
// Two of them (both equal to "10301") are palindromic.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of digits.
//

/**
 * @param {string} s
 * @return {number}
 */
var countPalindromes = function(s) {
    const mod = 1e9 + 7;
    const n = s.length;
    const leftCount = Array.from({ length: n }, () => new Array(10).fill(0));
    const rightCount = Array.from({ length: n }, () => new Array(10).fill(0));
    for (let i = 0; i < n; i++) {
        if (i > 0) {
            for (let d = 0; d < 10; d++) {
                leftCount[i][d] = leftCount[i - 1][d];
            }
        }
        leftCount[i][s.charCodeAt(i) - '0'.charCodeAt(0)]++;
    }
    for (let i = n - 1; i >= 0; i--) {
        if (i < n - 1) {
            for (let d = 0; d < 10; d++) {
                rightCount[i][d] = rightCount[i + 1][d];
            }
        }
        rightCount[i][s.charCodeAt(i) - '0'.charCodeAt(0)]++;
    }
    let result = 0;
    for (let i = 2; i < n - 2; i++) {
        for (let d1 = 0; d1 < 10; d1++) {
            for (let d2 = 0; d2 < 10; d2++) {
                result = (result + leftCount[i - 1][d1] * rightCount[i + 1][d2]) % mod;
            }
        }
    }
    return result;
};
