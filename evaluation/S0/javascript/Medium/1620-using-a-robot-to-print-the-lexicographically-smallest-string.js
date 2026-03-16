// Source: https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and a robot that currently holds an empty string t. Apply one of the following operations until s and t are both empty:
//
//
// 	Remove the first character of a string s and give it to the robot. The robot will append this character to the string t.
// 	Remove the last character of a string t and give it to the robot. The robot will write this character on paper.
//
//
// Return the lexicographically smallest string that can be written on the paper.
//
// Example:
// Input: s = "zza"
// Output: "azz"
// Explanation: Let p denote the written string.
// Initially p="", s="zza", t="".
// Perform first operation three times p="", s="", t="zza".
// Perform second operation three times p="azz", s="", t="".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var robotWithString = function(s) {
    const n = s.length;
    const charCount = new Array(26).fill(0);
    for (const char of s) {
        charCount[char.charCodeAt(0) - 97]++;
    }
    const tStack = [];
    let result = '';
    let minCharIndex = 0;
    let sIndex = 0;
    while (sIndex < n || tStack.length > 0) {
        while (sIndex < n && (tStack.length === 0 || (s.charCodeAt(sIndex) - 97) <= minCharIndex)) {
            const charIndex = s.charCodeAt(sIndex) - 97;
            charCount[charIndex]--;
            tStack.push(s[sIndex]);
            sIndex++;
        }
        while (minCharIndex < 26 && charCount[minCharIndex] === 0) {
            minCharIndex++;
        }
        if (tStack.length > 0) {
            result += tStack.pop();
        }
    }
    return result;
};
