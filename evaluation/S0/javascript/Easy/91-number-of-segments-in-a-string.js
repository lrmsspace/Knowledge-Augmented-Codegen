// Source: https://leetcode.com/problems/number-of-segments-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the number of segments in the string.
//
// A segment is defined to be a contiguous sequence of non-space characters.
//
// Example:
// Input: s = "Hello, my name is John"
// Output: 5
// Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]
//
// Constraints:
// 0 <= s.length <= 300
// 	s consists of lowercase and uppercase English letters, digits, or one of the following characters "!@#$%^&*()_+-=',.:".
// 	The only space character in s is ' '.
//

/**
 * @param {string} s
 * @return {number}
 */
var countSegments = function(s) {
    let count = 0;
    let inSegment = false;
    for (const char of s) {
        if (char !== ' ') {
            if (!inSegment) {
                count++;
                inSegment = true;
            }
        } else {
            inSegment = false;
        }
    }
    return count;
};