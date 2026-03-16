// Source: https://leetcode.com/problems/four-divisors/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors. If there is no such integer in the array, return 0.
//
// Example:
// Input: nums = [21,4,7]
// Output: 32
// Explanation: 
// 21 has 4 divisors: 1, 3, 7, 21
// 4 has 3 divisors: 1, 2, 4
// 7 has 2 divisors: 1, 7
// The answer is the sum of divisors of 21 only.
//
// Constraints:
// 1 <= nums.length <= 104
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumFourDivisors = function(nums) {
    let totalSum = 0;
    for (let num of nums) {
        let divisors = [];
        for (let i = 1; i <= Math.sqrt(num); i++) {
            if (num % i === 0) {
                divisors.push(i);
                if (i !== num / i) {
                    divisors.push(num / i);
                }
            }
            if (divisors.length > 4) {
                break;
            }
        }
        if (divisors.length === 4) {
            totalSum += divisors.reduce((a, b) => a + b, 0);
        }
    }
    return totalSum;
        
};
