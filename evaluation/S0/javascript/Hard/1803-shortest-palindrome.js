// Source: https://leetcode.com/problems/shortest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. You can convert s to a palindrome by adding characters in front of it.
//
// Return the shortest palindrome you can find by performing this transformation.
//
// Example:
// Input: s = "aacecaaa"
// Output: "aaacecaaa"
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of lowercase English letters only.
//

/**
 * @param {string} s
 * @return {string}
 */
var shortestPalindrome = function(s) {
    

    let rev = s.split('').reverse().join('');
    let l = s.length;
    for (let i = 0; i < l; i++) {
        if (s.substring(0, l - i) === rev.substring(i)) {
            return rev.substring(0, i) + s;
        }
    }
    return s;   
            
};
