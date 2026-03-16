// Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
//
// For example:
//
//
// 	"aaabbb" and "aaaaccc" are good captions.
// 	"aabbb" and "ccccd" are not good captions.
//
//
// You can perform the following operation any number of times:
//
// Choose an index i (where 0 <= i < n) and change the character at that index to either:
//
//
// 	The character immediately before it in the alphabet (if caption[i] != 'a').
// 	The character immediately after it in the alphabet (if caption[i] != 'z').
//
//
// Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
//
// Example:
// Input: caption = "cdcd"
//
// Output: "cccc"
//
// Explanation:
//
// It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
//
//
// 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
// 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
//
//
// Since "cccc" is lexicographically smaller than "dddd", return "cccc".
//
// Constraints:
// 1 <= caption.length <= 5 * 104
// 	caption consists only of lowercase English letters.
//

/**
 * @param {string} caption
 * @return {string}
 */
var minCostGoodCaption = function(caption) {
    const n = caption.length;
    const dp = Array.from({ length: n + 1 }, () => Array(3).fill(Infinity));
    const choice = Array.from({ length: n + 1 }, () => Array(3).fill(null));
    dp[0][0] = 0;
    for (let i = 1; i <= n; i++) {
        const charCode = caption.charCodeAt(i - 1);
        for (let len = 0; len < 3; len++) {
            for (let newCharCode = 97; newCharCode <= 122; newCharCode++) {
                const cost = (newCharCode === charCode) ? 0 : 1;
                if (len < 2) {
                    const newLen = len + 1;
                    if (dp[i][newLen] > dp[i - 1][len] + cost) {
                        dp[i][newLen] = dp[i - 1][len] + cost;
                        choice[i][newLen] = { prevLen: len, charCode: newCharCode };
                    }
                } else {    
                    for (let nextCharCode = 97; nextCharCode <= 122; nextCharCode++) {
                        if (nextCharCode !== newCharCode) {
                            if (dp[i][1] > dp[i - 1][len] + cost) {
                                dp[i][1] = dp[i - 1][len] + cost;
                                choice[i][1] = { prevLen: len, charCode: newCharCode };
                            }
                        }
                    }
                }
            }
        }
    }
    let minCost = Infinity;
    let lastLen = -1;
    for (let len = 0; len < 3; len++) {
        if (dp[n][len] < minCost) {
            minCost = dp[n][len];
            lastLen = len;
        }
    }
    if (minCost === Infinity) {
        return "";
    }
    const result = Array(n);;
    let currentLen = lastLen;
    for (let i = n; i >= 1; i--) {
        const { prevLen, charCode } = choice[i][currentLen];
        result[i - 1] = String.fromCharCode(charCode);
        currentLen = prevLen;
    }
    return result.join(''); 
};
