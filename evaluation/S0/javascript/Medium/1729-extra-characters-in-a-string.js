// Source: https://leetcode.com/problems/extra-characters-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string s and a dictionary of words dictionary. You have to break s into one or more non-overlapping substrings such that each substring is present in dictionary. There may be some extra characters in s which are not present in any of the substrings.
//
// Return the minimum number of extra characters left over if you break up s optimally.
//
// Example:
// Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
// Output: 1
// Explanation: We can break s in two substrings: "leet" from index 0 to 3 and "code" from index 5 to 8. There is only 1 unused character (at index 4), so we return 1.
//
// Constraints:
// 1 <= s.length <= 50
// 	1 <= dictionary.length <= 50
// 	1 <= dictionary[i].length <= 50
// 	dictionary[i] and s consists of only lowercase English letters
// 	dictionary contains distinct words
//

/**
 * @param {string} s
 * @param {string[]} dictionary
 * @return {number}
 */
var minExtraChar = function(s, dictionary) {
    const n = s.length;
    const dictSet = new Set(dictionary);
    const dp = new Array(n + 1).fill(0);

    for (let i = n - 1; i >= 0; i--) {
        dp[i] = dp[i + 1] + 1; // Assume the character at i is extra
        for (let j = i; j < n; j++) {
            const substring = s.slice(i, j + 1);
            if (dictSet.has(substring)) {
                dp[i] = Math.min(dp[i], dp[j + 1]);
            }
        }
    }   
    return dp[0];   
        
};
