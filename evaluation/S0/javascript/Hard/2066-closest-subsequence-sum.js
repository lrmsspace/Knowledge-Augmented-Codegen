// Source: https://leetcode.com/problems/closest-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer goal.
//
// You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).
//
// Return the minimum possible value of abs(sum - goal).
//
// Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.
//
// Example:
// Input: nums = [5,-7,3,5], goal = 6
// Output: 0
// Explanation: Choose the whole array as a subsequence, with a sum of 6.
// This is equal to the goal, so the absolute difference is 0.
//
// Constraints:
// 1 <= nums.length <= 40
// 	-107 <= nums[i] <= 107
// 	-109 <= goal <= 109
//

/**
 * @param {number[]} nums
 * @param {number} goal
 * @return {number}
 */
var minAbsDifference = function(nums, goal) {
    const n = nums.length;
    const leftSums = new Set();
    const rightSums = new Set();
    const generateSums = (index, currentSum, sums) => {
        if (index === n) {
            sums.add(currentSum);
            return;
        }
        generateSums(index + 1, currentSum, sums);
        generateSums(index + 1, currentSum + nums[index], sums);
    }
    generateSums(0, 0, leftSums);
    generateSums(Math.floor(n / 2), 0, rightSums);
    const sortedRightSums = Array.from(rightSums).sort((a, b) => a - b);
    let minDiff = Infinity;
    for (const leftSum of leftSums) {
        const target = goal - leftSum;
        const index = binarySearch(sortedRightSums, target);
        if (index < sortedRightSums.length) {
            minDiff = Math.min(minDiff, Math.abs(leftSum + sortedRightSums[index] - goal));
        }
        if (index > 0) {
            minDiff = Math.min(minDiff, Math.abs(leftSum + sortedRightSums[index - 1] - goal));
        }
    }
    return minDiff; 
};
