// Source: https://leetcode.com/problems/flip-string-to-monotone-increasing/   |   Difficulty: Medium
//
// Problem Description:
// A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).
//
// You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.
//
// Return the minimum number of flips to make s monotone increasing.
//
// Example:
// Input: s = "00110"
// Output: 1
// Explanation: We flip the last digit to get 00111.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

/**
 * @param {string} s
 * @return {number}
 */
var minFlipsMonoIncr = function(s) {
    const n = s.length;
    let flipToAllOnes = 0;
    let minFlips = 0;

    for (let char of s) {
        if (char === '0') {
            flipToAllOnes++;
        } else {
            minFlips = Math.min(minFlips + 1, flipToAllOnes);
        }
    }

    return minFlips;    
};
