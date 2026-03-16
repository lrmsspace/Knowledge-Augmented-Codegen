// Source: https://leetcode.com/problems/length-of-the-longest-valid-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string word and an array of strings forbidden.
//
// A string is called valid if none of its substrings are present in forbidden.
//
// Return the length of the longest valid substring of the string word.
//
// A substring is a contiguous sequence of characters in a string, possibly empty.
//
// Example:
// Input: word = "cbaaaabc", forbidden = ["aaa","cb"]
// Output: 4
// Explanation: There are 11 valid substrings in word: "c", "b", "a", "ba", "aa", "bc", "baa", "aab", "ab", "abc" and "aabc". The length of the longest valid substring is 4. 
// It can be shown that all other substrings contain either "aaa" or "cb" as a substring.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists only of lowercase English letters.
// 	1 <= forbidden.length <= 105
// 	1 <= forbidden[i].length <= 10
// 	forbidden[i] consists only of lowercase English letters.
//

/**
 * @param {string} word
 * @param {string[]} forbidden
 * @return {number}
 */
var longestValidSubstring = function(word, forbidden) {
    const forbiddenSet = new Set(forbidden);
    let maxLength = 0;
    let left = 0;
    for (let right = 0; right < word.length; right++) {
        for (let length = 1; length <= 10 && right - length + 1 >= left; length++) {
            const substring = word.substring(right - length + 1, right + 1);
            if (forbiddenSet.has(substring)) {
                left = right - length + 2;
                break;
            }
        }
        maxLength = Math.max(maxLength, right - left + 1);
    }
    return maxLength;
};
