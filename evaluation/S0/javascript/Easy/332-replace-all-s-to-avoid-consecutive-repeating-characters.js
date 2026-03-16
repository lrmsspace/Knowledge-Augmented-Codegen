// Source: https://leetcode.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s containing only lowercase English letters and the '?' character, convert all the '?' characters into lowercase letters such that the final string does not contain any consecutive repeating characters. You cannot modify the non '?' characters.
//
// It is guaranteed that there are no consecutive repeating characters in the given string except for '?'.
//
// Return the final string after all the conversions (possibly zero) have been made. If there is more than one solution, return any of them. It can be shown that an answer is always possible with the given constraints.
//
// Example:
// Input: s = "?zs"
// Output: "azs"
// Explanation: There are 25 solutions for this problem. From "azs" to "yzs", all are valid. Only "z" is an invalid modification as the string will consist of consecutive repeating characters in "zzs".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consist of lowercase English letters and '?'.
//

/**
 * @param {string} s
 * @return {string}
 */
var modifyString = function(s) {
    const n = s.length;
    const chars = s.split('');
    const alphabet = 'abcdefghijklmnopqrstuvwxyz';
    for (let i = 0; i < n; i++) {
        if (chars[i] === '?') {
            for (const letter of alphabet) {
                if ((i === 0 || chars[i - 1] !== letter) && (i === n - 1 || chars[i + 1] !== letter)) {
                    chars[i] = letter;
                    break;
                }
            }
        }
    }
    return chars.join('');
};