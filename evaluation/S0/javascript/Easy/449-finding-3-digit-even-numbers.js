// Source: https://leetcode.com/problems/finding-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array digits, where each element is a digit. The array may contain duplicates.
//
// You need to find all the unique integers that follow the given requirements:
//
//
// 	The integer consists of the concatenation of three elements from digits in any arbitrary order.
// 	The integer does not have leading zeros.
// 	The integer is even.
//
//
// For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
//
// Return a sorted array of the unique integers.
//
// Example:
// Input: digits = [2,1,3,0]
// Output: [102,120,130,132,210,230,302,310,312,320]
// Explanation: All the possible integers that follow the requirements are in the output array. 
// Notice that there are no odd integers or integers with leading zeros.
//
// Constraints:
// 3 <= digits.length <= 100
// 	0 <= digits[i] <= 9
//

/**
 * @param {number[]} digits
 * @return {number[]}
 */
var findEvenNumbers = function(digits) {
    const resultSet = new Set();
    const n = digits.length;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            for (let k = 0; k < n; k++) {
                if (i !== j && j !== k && i !== k) {
                    const num = digits[i] * 100 + digits[j] * 10 + digits[k];
                    if (num >= 100 && num % 2 === 0) {
                        resultSet.add(num);
                    }
                }
            }
        }
    }
    return Array.from(resultSet).sort((a, b) => a - b);
};