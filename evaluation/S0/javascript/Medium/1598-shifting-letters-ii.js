// Source: https://leetcode.com/problems/shifting-letters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of lowercase English letters and a 2D integer array shifts where shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward if directioni = 0.
//
// Shifting a character forward means replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').
//
// Return the final string after all such shifts to s are applied.
//
// Example:
// Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
// Output: "ace"
// Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
// Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
// Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".
//
// Constraints:
// 1 <= s.length, shifts.length <= 5 * 104
// 	shifts[i].length == 3
// 	0 <= starti <= endi < s.length
// 	0 <= directioni <= 1
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number[][]} shifts
 * @return {string}
 */
var shiftingLetters = function(s, shifts) {
    const n = s.length;
    const diff = new Array(n + 1).fill(0);

    for (const [start, end, direction] of shifts) {
        diff[start] += direction === 1 ? 1 : -1;
        diff[end + 1] += direction === 1 ? -1 : 1;
    }

    let shift = 0;
    const result = [];

    for (let i = 0; i < n; i++) {
        shift += diff[i];
        const charCode = s.charCodeAt(i) - 97;
        const newCharCode = (charCode + shift + 26) % 26;
        result.push(String.fromCharCode(newCharCode + 97));
    }

    return result.join('');
};