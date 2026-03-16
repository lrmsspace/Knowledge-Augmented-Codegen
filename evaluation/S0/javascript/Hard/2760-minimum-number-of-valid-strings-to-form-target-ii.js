// Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words and a string target.
//
// A string x is called valid if x is a prefix of any string in words.
//
// Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.
//
// Example:
// Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
//
// Output: 3
//
// Explanation:
//
// The target string can be formed by concatenating:
//
//
// 	Prefix of length 2 of words[1], i.e. "aa".
// 	Prefix of length 3 of words[2], i.e. "bcd".
// 	Prefix of length 3 of words[0], i.e. "abc".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 5 * 104
// 	The input is generated such that sum(words[i].length) <= 105.
// 	words[i] consists only of lowercase English letters.
// 	1 <= target.length <= 5 * 104
// 	target consists only of lowercase English letters.
//

/**
 * @param {string[]} words
 * @param {string} target
 * @return {number}
 */
var minValidStrings = function(words, target) {
    const n = target.length;
    const dp = Array(n + 1).fill(Infinity);
    dp[0] = 0;
    const wordSet = new Set(words);
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < i; j++) {
            const substring = target.slice(j, i);
            for (const word of wordSet) {
                if (word.startsWith(substring)) {
                    dp[i] = Math.min(dp[i], dp[j] + 1);
                    break;
                }
            }
        }
    }
    return dp[n] === Infinity ? -1 : dp[n]; 
};
