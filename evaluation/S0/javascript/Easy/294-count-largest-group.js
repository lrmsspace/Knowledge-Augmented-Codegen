// Source: https://leetcode.com/problems/count-largest-group/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n.
//
// We need to group the numbers from 1 to n according to the sum of its digits. For example, the numbers 14 and 5 belong to the same group, whereas 13 and 3 belong to different groups.
//
// Return the number of groups that have the largest size, i.e. the maximum number of elements.
//
// Example:
// Input: n = 13
// Output: 4
// Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
// [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
// There are 4 groups with largest size.
//
// Constraints:
// 1 <= n <= 104
//

/**
 * @param {number} n
 * @return {number}
 */
var countLargestGroup = function(n) {
    const digitSumMap = new Map();
    const getDigitSum = (num) => {
        let sum = 0;
        while (num > 0) {
            sum += num % 10;
            num = Math.floor(num / 10);
        }
        return sum;
    };
    for (let i = 1; i <= n; i++) {
        const digitSum = getDigitSum(i);
        digitSumMap.set(digitSum, (digitSumMap.get(digitSum) || 0) + 1);
    }
    let maxSize = 0;
    for (const size of digitSumMap.values()) {
        if (size > maxSize) {
            maxSize = size;
        }
    }
    let count = 0;
    for (const size of digitSumMap.values()) {
        if (size === maxSize) {
            count++;
        }
    }
    return count;
};