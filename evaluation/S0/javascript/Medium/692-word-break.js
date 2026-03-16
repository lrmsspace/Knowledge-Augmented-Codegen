// Source: https://leetcode.com/problems/word-break/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
//
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
//
// Example:
// Input: s = "leetcode", wordDict = ["leet","code"]
// Output: true
// Explanation: Return true because "leetcode" can be segmented as "leet code".
//
// Constraints:
// 1 <= s.length <= 300
// 	1 <= wordDict.length <= 1000
// 	1 <= wordDict[i].length <= 20
// 	s and wordDict[i] consist of only lowercase English letters.
// 	All the strings of wordDict are unique.
//

/**
 * @param {string} s
 * @param {string[]} wordDict
 * @return {boolean}
 */
var wordBreak = function(s, wordDict) {
    const wordSet = new Set(wordDict);
    const dp = new Array(s.length + 1).fill(false);
    dp[0] = true; // Empty string can be segmented

    for (let i = 1; i <= s.length; i++) {
        for (let j = 0; j < i; j++) {
            if (dp[j] && wordSet.has(s.substring(j, i))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[s.length];
};