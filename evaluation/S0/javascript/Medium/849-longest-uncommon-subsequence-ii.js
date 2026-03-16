// Source: https://leetcode.com/problems/longest-uncommon-subsequence-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
//
// An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
//
// A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
//
//
// 	For example, "abc" is a subsequence of "aebdc" because you can delete the underlined characters in "aebdc" to get "abc". Other subsequences of "aebdc" include "aebdc", "aeb", and "" (empty string).
//
// Example:
// Input: strs = ["aba","cdc","eae"]
// Output: 3
//
// Constraints:
// 2 <= strs.length <= 50
// 	1 <= strs[i].length <= 10
// 	strs[i] consists of lowercase English letters.
//

/**
 * @param {string[]} strs
 * @return {number}
 */
var findLUSlength = function(strs) {
    const isSubsequence = (s, t) => {
        let i = 0, j = 0;
        while (i < s.length && j < t.length) {
            if (s[i] === t[j]) {
                i++;
            }
            j++;
        }
        return i === s.length;
    };

    strs.sort((a, b) => b.length - a.length);

    for (let i = 0; i < strs.length; i++) {
        let isUncommon = true;
        for (let j = 0; j < strs.length; j++) {
            if (i !== j && isSubsequence(strs[i], strs[j])) {
                isUncommon = false;
                break;
            }
        }
        if (isUncommon) {
            return strs[i].length;
        }
    }

    return -1;
};