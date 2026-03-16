// Source: https://leetcode.com/problems/count-symmetric-integers/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers low and high.
//
// An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is equal to the sum of the last n digits of x. Numbers with an odd number of digits are never symmetric.
//
// Return the number of symmetric integers in the range [low, high].
//
// Example:
// Input: low = 1, high = 100
// Output: 9
// Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.
//
// Constraints:
// 1 <= low <= high <= 104
//

/**
 * @param {number} low
 * @param {number} high
 * @return {number}
 */
var countSymmetricIntegers = function(low, high) {
    let count = 0;
    for (let num = low; num <= high; num++) {
        const strNum = num.toString();
        if (strNum.length % 2 === 0) {
            const half = strNum.length / 2;
            const firstHalf = strNum.slice(0, half);
            const secondHalf = strNum.slice(half);
            const sumFirstHalf = firstHalf.split('').reduce((acc, digit) => acc + Number(digit), 0);
            const sumSecondHalf = secondHalf.split('').reduce((acc, digit) => acc + Number(digit), 0);
            if (sumFirstHalf === sumSecondHalf) {
                count++;
            }
        }
    }
    return count;
};