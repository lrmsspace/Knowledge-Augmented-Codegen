// Source: https://leetcode.com/problems/sum-of-unique-elements/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. The unique elements of an array are the elements that appear exactly once in the array.
//
// Return the sum of all the unique elements of nums.
//
// Example:
// Input: nums = [1,2,3,2]
// Output: 4
// Explanation: The unique elements are [1,3], and the sum is 4.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumOfUnique = function(nums) {
    const frequency = new Array(101).fill(0);
    for (const num of nums) {
        frequency[num]++;
    }
    let sum = 0;
    for (let i = 1; i <= 100; i++) {
        if (frequency[i] === 1) {
            sum += i;
        }
    }
    return sum;
};