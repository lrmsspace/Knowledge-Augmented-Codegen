// Source: https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/   |   Difficulty: Easy
//
// Problem Description:
// Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).
//
// Example:
// Input: low = 3, high = 7
// Output: 3
// Explanation: The odd numbers between 3 and 7 are [3,5,7].
//
// Constraints:
// 0 <= low <= high <= 10^9
//

/**
 * @param {number} low
 * @param {number} high
 * @return {number}
 */
var countOdds = function(low, high) {
    const totalNumbers = high - low + 1;
    if (totalNumbers % 2 === 0) {
        return totalNumbers / 2;
    } else {
        if (low % 2 === 1 || high % 2 === 1) {
            return Math.floor(totalNumbers / 2) + 1;
        } else {
            return Math.floor(totalNumbers / 2);
        }
    }   return count;
};
