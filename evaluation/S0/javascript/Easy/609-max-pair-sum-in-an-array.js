// Source: https://leetcode.com/problems/max-pair-sum-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. You have to find the maximum sum of a pair of numbers from nums such that the largest digit in both numbers is equal.
//
// For example, 2373 is made up of three distinct digits: 2, 3, and 7, where 7 is the largest among them.
//
// Return the maximum sum or -1 if no such pair exists.
//
// Example:
// Input: nums = [112,131,411]
//
// Output: -1
//
// Explanation:
//
// Each numbers largest digit in order is [2,3,4].
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSum = function(nums) {
    const digitMap = new Map();
    let maxPairSum = -1;
    for (const num of nums) {
        const largestDigit = Math.max(...String(num).split('').map(Number));
        if (!digitMap.has(largestDigit)) {
            digitMap.set(largestDigit, []);
        }
        digitMap.get(largestDigit).push(num);
    }
    for (const [digit, numbers] of digitMap.entries()) {
        if (numbers.length >= 2) {
            numbers.sort((a, b) => b - a);
            const pairSum = numbers[0] + numbers[1];
            maxPairSum = Math.max(maxPairSum, pairSum);
        }
    }
    return maxPairSum;
};
