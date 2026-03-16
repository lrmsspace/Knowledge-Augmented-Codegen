// Source: https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.
//
// The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.
//
// Return the minimum number of operations needed to make s alternating.
//
// Example:
// Input: s = "0100"
// Output: 1
// Explanation: If you change the last character to '1', s will be "0101", which is alternating.
//
// Constraints:
// 1 <= s.length <= 104
// 	s[i] is either '0' or '1'.
//

/**
 * @param {string} s
 * @return {number}
 */
var minOperations = function(s) {
    let count1 = 0; // Count for pattern "0101..."
    let count2 = 0; // Count for pattern "1010..."
    for (let i = 0; i < s.length; i++) {
        const expectedChar1 = i % 2 === 0 ? '0' : '1';
        const expectedChar2 = i % 2 === 0 ? '1' : '0';
        if (s[i] !== expectedChar1) {
            count1++;
        }
        if (s[i] !== expectedChar2) {
            count2++;
        }
    }
    return Math.min(count1, count2);    
};
