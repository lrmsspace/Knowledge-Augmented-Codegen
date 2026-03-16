// Source: https://leetcode.com/problems/valid-palindrome/   |   Difficulty: Easy
//
// Problem Description:
// A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.
//
// Given a string s, return true if it is a palindrome, or false otherwise.
//
// Example:
// Input: s = "A man, a plan, a canal: Panama"
// Output: true
// Explanation: "amanaplanacanalpanama" is a palindrome.
//
// Constraints:
// 1 <= s.length <= 2 * 105
// 	s consists only of printable ASCII characters.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var isPalindrome = function(s) {
    // Normalize the string: convert to lowercase and remove non-alphanumeric characters
    const normalizedStr = s.toLowerCase().replace(/[^a-z0-9]/g, '');
    
    // Initialize two pointers
    let left = 0;
    let right = normalizedStr.length - 1;
    
    // Check for palindrome
    while (left < right) {
        if (normalizedStr[left] !== normalizedStr[right]) {
            return false; // Not a palindrome
        }
        left++;
        right--;
    }
    
    return true; // Is a palindrome 
};
