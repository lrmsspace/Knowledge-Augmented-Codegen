// Source: https://leetcode.com/problems/longest-palindrome/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.
//
// Letters are case sensitive, for example, "Aa" is not considered a palindrome.
//
// Example:
// Input: s = "abccccdd"
// Output: 7
// Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.
//
// Constraints:
// 1 <= s.length <= 2000
// 	s consists of lowercase and/or uppercase English letters only.
//

/**
 * @param {string} s
 * @return {number}
 */
var longestPalindrome = function(s) {
    const charCount = new Array(52).fill(0);        
    for (const char of s) {
        const index = char >= 'a' ? char.charCodeAt(0) - 97 + 26 : char.charCodeAt(0) - 65;
        charCount[index]++;
    }   
    let length = 0;
    let oddFound = false;
    for (const count of charCount) {
        if (count % 2 === 0) {
            length += count;
        } else {
            length += count - 1;
            oddFound = true;
        }
    }
    if (oddFound) {
        length += 1;
    }
    return length;
};