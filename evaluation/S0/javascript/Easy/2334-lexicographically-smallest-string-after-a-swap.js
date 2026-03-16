// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-a-swap/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s containing only digits, return the lexicographically smallest string that can be obtained after swapping adjacent digits in s with the same parity at most once.
//
// Digits have the same parity if both are odd or both are even. For example, 5 and 9, as well as 2 and 4, have the same parity, while 6 and 9 do not.
//
// Example:
// Input: s = "45320"
//
// Output: "43520"
//
// Explanation: 
//
// s[1] == '5' and s[2] == '3' both have the same parity, and swapping them results in the lexicographically smallest string.
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists only of digits.
//

/**
 * @param {string} s
 * @return {string}
 */
var getSmallestString = function(s) {
    const chars = s.split('');
    const n = chars.length;
    for (let i = 0; i < n - 1; i++) {
        if ((chars[i] % 2 === chars[i + 1] % 2) && chars[i] > chars[i + 1]) {
            [chars[i], chars[i + 1]] = [chars[i + 1], chars[i]];
            break;
        }
    }
    return chars.join('');
};