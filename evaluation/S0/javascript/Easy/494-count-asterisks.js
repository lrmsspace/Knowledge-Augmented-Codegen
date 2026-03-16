// Source: https://leetcode.com/problems/count-asterisks/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s, where every two consecutive vertical bars '|' are grouped into a pair. In other words, the 1st and 2nd '|' make a pair, the 3rd and 4th '|' make a pair, and so forth.
//
// Return the number of '*' in s, excluding the '*' between each pair of '|'.
//
// Note that each '|' will belong to exactly one pair.
//
// Example:
// Input: s = "l|*e*et|c**o|*de|"
// Output: 2
// Explanation: The considered characters are underlined: "l|*e*et|c**o|*de|".
// The characters between the first and second '|' are excluded from the answer.
// Also, the characters between the third and fourth '|' are excluded from the answer.
// There are 2 asterisks considered. Therefore, we return 2.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters, vertical bars '|', and asterisks '*'.
// 	s contains an even number of vertical bars '|'.
//

/**
 * @param {string} s
 * @return {number}
 */
var countAsterisks = function(s) {
    let count = 0;
    let inPair = false;
    for (const char of s) {
        if (char === '|') {
            inPair = !inPair;
        } else if (char === '*' && !inPair) {
            count++;
        }
    }
    return count;
};