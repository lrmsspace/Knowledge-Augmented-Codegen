// Source: https://leetcode.com/problems/remove-adjacent-almost-equal-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string word.
//
// In one operation, you can pick any index i of word and change word[i] to any lowercase English letter.
//
// Return the minimum number of operations needed to remove all adjacent almost-equal characters from word.
//
// Two characters a and b are almost-equal if a == b or a and b are adjacent in the alphabet.
//
// Example:
// Input: word = "aaaaa"
// Output: 2
// Explanation: We can change word into "acaca" which does not have any adjacent almost-equal characters.
// It can be shown that the minimum number of operations needed to remove all adjacent almost-equal characters from word is 2.
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists only of lowercase English letters.
//

/**
 * @param {string} word
 * @return {number}
 */
var removeAlmostEqualCharacters = function(word) {
    const n = word.length;
    const dp = Array.from({ length: n + 1 }, () => Array(2).fill(Infinity));
    dp[0][0] = 0;
    for (let i = 1; i <= n; i++) {
        const currCharCode = word.charCodeAt(i - 1);
        // Not change current character
        if (i === 1) {
            dp[i][0] = dp[i - 1][0];
        } else {
            const prevCharCode = word.charCodeAt(i - 2);
            if (Math.abs(currCharCode - prevCharCode) > 1) {
                dp[i][0] = Math.min(dp[i][0], dp[i - 1][0]);
            }
            dp[i][0] = Math.min(dp[i][0], dp[i - 1][1]);
        }
        // Change current character
        dp[i][1] = Math.min(dp[i - 1][0], dp[i - 1][1]) + 1;
    }
    return Math.min(dp[n][0], dp[n][1]);
};
