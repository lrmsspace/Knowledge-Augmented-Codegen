// Source: https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/   |   Difficulty: Hard
//
// Problem Description:
// You are given a list of strings of the same length words and a string target.
//
// Your task is to form target using the given words under the following rules:
//
//
// 	target should be formed from left to right.
// 	To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
// 	Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
// 	Repeat the process until you form the string target.
//
//
// Notice that you can use multiple characters from the same string in words provided the conditions above are met.
//
// Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: words = ["acca","bbbb","caca"], target = "aba"
// Output: 6
// Explanation: There are 6 ways to form target.
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 1000
// 	All strings in words have the same length.
// 	1 <= target.length <= 1000
// 	words[i] and target contain only lowercase English letters.
//

/**
 * @param {string[]} words
 * @param {string} target
 * @return {number}
 */
var numWays = function(words, target) {
    const MOD = 1e9 + 7;
    const m = words.length;
    const n = words[0].length;
    const targetLength = target.length;
    const charCount = Array.from({ length: n }, () => new Array(26).fill(0));
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            charCount[j][words[i].charCodeAt(j) - 97]++;
        }
    }
    const dp = new Array(targetLength + 1).fill(0);
    dp[0] = 1;
    for (let j = 0; j < n; j++) {
        for (let i = targetLength - 1; i >= 0; i--) {
            const charIndex = target.charCodeAt(i) - 97;
            dp[i + 1] = (dp[i + 1] + dp[i] * charCount[j][charIndex]) % MOD;
        }
    }
    return dp[targetLength];
};
