// Source: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums consisting of 3 * n elements.
//
// You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:
//
//
// 	The first n elements belonging to the first part and their sum is sumfirst.
// 	The next n elements belonging to the second part and their sum is sumsecond.
//
//
// The difference in sums of the two parts is denoted as sumfirst - sumsecond.
//
//
// 	For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
// 	Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
//
//
// Return the minimum difference possible between the sums of the two parts after the removal of n elements.
//
// Example:
// Input: nums = [3,1,2]
// Output: -1
// Explanation: Here, nums has 3 elements, so n = 1. 
// Thus we have to remove 1 element from nums and divide the array into two equal parts.
// - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
// - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
// - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
// The minimum difference between sums of the two parts is min(-1,1,2) = -1.
//
// Constraints:
// nums.length == 3 * n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumDifference = function(nums) {
    const n = nums.length / 3;
    const leftMaxHeap = [];
    const rightMinHeap = [];
    let leftSum = 0;
    let rightSum = 0;
    for (let i = 0; i < n; i++) {
        leftSum += nums[i];
        rightSum += nums[2 * n + i];
        leftMaxHeap.push(nums[i]);
        rightMinHeap.push(nums[2 * n + i]);
    }
    leftMaxHeap.sort((a, b) => b - a);
    rightMinHeap.sort((a, b) => a - b);
    let minDiff = leftSum - rightSum;
    for (let i = n - 1; i >= 0; i--) {
        leftSum -= leftMaxHeap[0];
        rightSum -= rightMinHeap[0];
        leftMaxHeap.shift();
        rightMinHeap.shift();
        leftSum += nums[n + i];
        rightSum += nums[n + i];
        leftMaxHeap.push(nums[n + i]);
        rightMinHeap.push(nums[n + i]);
        leftMaxHeap.sort((a, b) => b - a);
        rightMinHeap.sort((a, b) => a - b);
        minDiff = Math.min(minDiff, leftSum - rightSum);
    }
    return minDiff;
};
