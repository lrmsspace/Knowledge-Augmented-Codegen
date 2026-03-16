// Source: https://leetcode.com/problems/find-greatest-common-divisor-of-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the greatest common divisor of the smallest number and largest number in nums.
//
// The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.
//
// Example:
// Input: nums = [2,5,6,9,10]
// Output: 2
// Explanation:
// The smallest number in nums is 2.
// The largest number in nums is 10.
// The greatest common divisor of 2 and 10 is 2.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var findGCD = function(nums) {
    const gcd = (a, b) => {
        while (b !== 0) {
            const temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    };
    const minNum = Math.min(...nums);
    const maxNum = Math.max(...nums);
    return gcd(minNum, maxNum);
};
