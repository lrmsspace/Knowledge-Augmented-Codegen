// Source: https://leetcode.com/problems/maximum-odd-binary-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s that contains at least one '1'.
//
// You have to rearrange the bits in such a way that the resulting binary number is the maximum odd binary number that can be created from this combination.
//
// Return a string representing the maximum odd binary number that can be created from the given combination.
//
// Note that the resulting string can have leading zeros.
//
// Example:
// Input: s = "010"
// Output: "001"
// Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of '0' and '1'.
// 	s contains at least one '1'.
//

/**
 * @param {string} s
 * @return {string}
 */
var maximumOddBinaryNumber = function(s) {
    const onesCount = [...s].filter(bit => bit === '1').length;
    const zerosCount = s.length - onesCount;
    return '0'.repeat(zerosCount) + '1'.repeat(onesCount - 1) + '1';    
};
