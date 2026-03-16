// Source: https://leetcode.com/problems/number-of-good-ways-to-split-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s.
//
// A split is called good if you can split s into two non-empty strings sleft and sright where their concatenation is equal to s (i.e., sleft + sright = s) and the number of distinct letters in sleft and sright is the same.
//
// Return the number of good splits you can make in s.
//
// Example:
// Input: s = "aacaba"
// Output: 2
// Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
// ("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
// ("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
// ("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
// ("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
// ("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var numSplits = function(s) {
    const n = s.length;
    const leftCount = new Array(n).fill(0);
    const rightCount = new Array(n).fill(0);
    const leftSet = new Set();
    const rightSet = new Set();

    for (let i = 0; i < n; i++) {
        leftSet.add(s[i]);
        leftCount[i] = leftSet.size;
    }

    for (let i = n - 1; i >= 0; i--) {
        rightSet.add(s[i]);
        rightCount[i] = rightSet.size;
    }

    let goodSplits = 0;
    for (let i = 0; i < n - 1; i++) {
        if (leftCount[i] === rightCount[i + 1]) {
            goodSplits++;
        }
    }

    return goodSplits;
};