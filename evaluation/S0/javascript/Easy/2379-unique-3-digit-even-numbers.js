// Source: https://leetcode.com/problems/unique-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of digits called digits. Your task is to determine the number of distinct three-digit even numbers that can be formed using these digits.
//
// Note: Each copy of a digit can only be used once per number, and there may not be leading zeros.
//
// Example:
// Input: digits = [1,2,3,4]
//
// Output: 12
//
// Explanation: The 12 distinct 3-digit even numbers that can be formed are 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222 cannot be formed because there is only 1 copy of the digit 2.
//
// Constraints:
// 3 <= digits.length <= 10
// 	0 <= digits[i] <= 9
//

/**
 * @param {number[]} digits
 * @return {number}
 */
var totalNumbers = function(digits) {
    const uniqueNumbers = new Set();
    const n = digits.length;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            for (let k = 0; k < n; k++) {
                if (i !== j && j !== k && i !== k) {
                    const hundreds = digits[i];
                    const tens = digits[j];
                    const units = digits[k];
                    const number = hundreds * 100 + tens * 10 + units;
                    if (hundreds !== 0 && units % 2 === 0) {
                        uniqueNumbers.add(number);
                    }
                }
            }
        }
    }
    return uniqueNumbers.size;  
};
