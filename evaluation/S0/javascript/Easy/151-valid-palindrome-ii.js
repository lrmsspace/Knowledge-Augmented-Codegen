// Source: https://leetcode.com/problems/valid-palindrome-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return true if the s can be palindrome after deleting at most one character from it.
//
// Example:
// Input: s = "aba"
// Output: true
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var validPalindrome = function(s) {
    function isPalindromeRange(left, right) {
        while (left < right) {
            if (s[left] !== s[right]) return false;
            left++;
            right--;
        }   
        return true;
    }   
    let left = 0;   
    let right = s.length - 1;
    while (left < right) {
        if (s[left] !== s[right]) {
            return isPalindromeRange(left + 1, right) || isPalindromeRange(left, right - 1);
        }
        left++;
        right--;
    }
    return true;
    
};
