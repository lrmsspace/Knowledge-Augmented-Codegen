// Source: https://leetcode.com/problems/to-lower-case/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the string after replacing every uppercase letter with the same lowercase letter.
//
// Example:
// Input: s = "Hello"
// Output: "hello"
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of printable ASCII characters.
//

/**
 * @param {string} s
 * @return {string}
 */
var toLowerCase = function(s) {
    let result = '';
    for (let i = 0; i < s.length; i++) {
        let charCode = s.charCodeAt(i);
        if (charCode >= 65 && charCode <= 90) {
            result += String.fromCharCode(charCode + 32);
        } else {
            result += s[i];
        }
    }
    return result;
    
};
