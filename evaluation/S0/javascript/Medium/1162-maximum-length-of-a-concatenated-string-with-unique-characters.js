// Source: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
//
// Return the maximum possible length of s.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: arr = ["un","iq","ue"]
// Output: 4
// Explanation: All the valid concatenations are:
// - ""
// - "un"
// - "iq"
// - "ue"
// - "uniq" ("un" + "iq")
// - "ique" ("iq" + "ue")
// Maximum length is 4.
//
// Constraints:
// 1 <= arr.length <= 16
// 	1 <= arr[i].length <= 26
// 	arr[i] contains only lowercase English letters.
//

/**
 * @param {string[]} arr
 * @return {number}
 */
var maxLength = function(arr) {
    let maxLen = 0;
    const n = arr.length;
    const isUnique = (s) => {
        const charSet = new Set();
        for (const char of s) {
            if (charSet.has(char)) return false;
            charSet.add(char);
        }
        return true;
    };
    const backtrack = (index, current) => {
        if (index === n) {
            maxLen = Math.max(maxLen, current.length);
            return;
        }
        backtrack(index + 1, current);
        const next = current + arr[index];
        if (isUnique(next)) {
            backtrack(index + 1, next);
        }
    };
    backtrack(0, "");
    return maxLen;  
            
};
