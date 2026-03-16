// Source: https://leetcode.com/problems/reconstruct-original-digits-from-english/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.
//
// Example:
// Input: s = "owoztneoer"
// Output: "012"
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
// 	s is guaranteed to be valid.
//

/**
 * @param {string} s
 * @return {string}
 */
var originalDigits = function(s) {
    const count = Array(10).fill(0);
    const charCount = {};
    for (const char of s) {
        charCount[char] = (charCount[char] || 0) + 1;
    }
    count[0] = charCount['z'] || 0;
    count[2] = charCount['w'] || 0;
    count[4] = charCount['u'] || 0;
    count[6] = charCount['x'] || 0;
    count[8] = charCount['g'] || 0;
    count[3] = (charCount['h'] || 0) - count[8];
    count[5] = (charCount['f'] || 0) - count[4];
    count[7] = (charCount['s'] || 0) - count[6];
    count[1] = (charCount['o'] || 0) - count[0] - count[2] - count[4];
    count[9] = (charCount['i'] || 0) - count[5] - count[6] - count[8];
    let result = '';
    for (let i = 0; i <= 9; i++) {
        result += i.toString().repeat(count[i]);
    }
    return result;  
};
