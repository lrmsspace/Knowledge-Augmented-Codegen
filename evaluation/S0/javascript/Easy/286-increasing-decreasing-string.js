// Source: https://leetcode.com/problems/increasing-decreasing-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s. Reorder the string using the following algorithm:
//
//
// 	Remove the smallest character from s and append it to the result.
// 	Remove the smallest character from s that is greater than the last appended character, and append it to the result.
// 	Repeat step 2 until no more characters can be removed.
// 	Remove the largest character from s and append it to the result.
// 	Remove the largest character from s that is smaller than the last appended character, and append it to the result.
// 	Repeat step 5 until no more characters can be removed.
// 	Repeat steps 1 through 6 until all characters from s have been removed.
//
//
// If the smallest or largest character appears more than once, you may choose any occurrence to append to the result.
//
// Return the resulting string after reordering s using this algorithm.
//
// Example:
// Input: s = "aaaabbbbcccc"
// Output: "abccbaabccba"
// Explanation: After steps 1, 2 and 3 of the first iteration, result = "abc"
// After steps 4, 5 and 6 of the first iteration, result = "abccba"
// First iteration is done. Now s = "aabbcc" and we go back to step 1
// After steps 1, 2 and 3 of the second iteration, result = "abccbaabc"
// After steps 4, 5 and 6 of the second iteration, result = "abccbaabccba"
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var sortString = function(s) {
    const charCount = Array(26).fill(0);
    for (const char of s) {
        charCount[char.charCodeAt(0) - 97]++;
    }
    let result = '';
    while (result.length < s.length) {
        for (let i = 0; i < 26; i++) {
            if (charCount[i] > 0) {
                result += String.fromCharCode(i + 97);
                charCount[i]--;
            }
        }
        for (let i = 25; i >= 0; i--) {
            if (charCount[i] > 0) {
                result += String.fromCharCode(i + 97);
                charCount[i]--;
            }
        }
    }
    return result;
};