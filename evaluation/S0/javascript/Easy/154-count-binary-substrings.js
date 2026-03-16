// Source: https://leetcode.com/problems/count-binary-substrings/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s, return the number of non-empty substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.
//
// Substrings that occur multiple times are counted the number of times they occur.
//
// Example:
// Input: s = "00110011"
// Output: 6
// Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
// Notice that some of these substrings repeat and are counted the number of times they occur.
// Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

/**
 * @param {string} s
 * @return {number}
 */
var countBinarySubstrings = function(s) {
    let prevRunLength = 0;
    let currRunLength = 1;
    let count = 0;
    for (let i = 1; i < s.length; i++) {
        if (s[i] === s[i - 1]) {
            currRunLength++;
        } else {
            count += Math.min(prevRunLength, currRunLength);
            prevRunLength = currRunLength;
            currRunLength = 1;
        }
    }
    count += Math.min(prevRunLength, currRunLength);
    return count;
    
};
