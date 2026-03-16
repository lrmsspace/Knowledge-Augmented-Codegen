// Source: https://leetcode.com/problems/minimize-string-length/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, you have two types of operation:
//
//
// 	Choose an index i in the string, and let c be the character in position i. Delete the closest occurrence of c to the left of i (if exists).
// 	Choose an index i in the string, and let c be the character in position i. Delete the closest occurrence of c to the right of i (if exists).
//
//
// Your task is to minimize the length of s by performing the above operations zero or more times.
//
// Return an integer denoting the length of the minimized string.
//
// Example:
// Input: s = "aaabc"
//
// Output: 3
//
// Explanation:
//
//
// 	Operation 2: we choose i = 1 so c is 'a', then we remove s[2] as it is closest 'a' character to the right of s[1].
// 	s becomes "aabc" after this.
// 	Operation 1: we choose i = 1 so c is 'a', then we remove s[0] as it is closest 'a' character to the left of s[1].
// 	s becomes "abc" after this.
//
// Constraints:
// 1 <= s.length <= 100
// 	s contains only lowercase English letters
//

/**
 * @param {string} s
 * @return {number}
 */
var minimizedStringLength = function(s) {
    const uniqueChars = new Set(s);
    return uniqueChars.size;        
};
