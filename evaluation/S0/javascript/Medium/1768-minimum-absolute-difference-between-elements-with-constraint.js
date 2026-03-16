// Source: https://leetcode.com/problems/minimum-absolute-difference-between-elements-with-constraint/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer x.
//
// Find the minimum absolute difference between two elements in the array that are at least x indices apart.
//
// In other words, find two indices i and j such that abs(i - j) >= x and abs(nums[i] - nums[j]) is minimized.
//
// Return an integer denoting the minimum absolute difference between two elements that are at least x indices apart.
//
// Example:
// Input: nums = [4,3,2,4], x = 2
// Output: 0
// Explanation: We can select nums[0] = 4 and nums[3] = 4. 
// They are at least 2 indices apart, and their absolute difference is the minimum, 0. 
// It can be shown that 0 is the optimal answer.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= x < nums.length
//

/**
 * @param {number[]} nums
 * @param {number} x
 * @return {number}
 */
var minAbsoluteDifference = function(nums, x) {
    const sortedList = [];
    let minDiff = Infinity;
    for (let i = x; i < nums.length; i++) {
        const target = nums[i];
        let left = 0;
        let right = sortedList.length - 1;
        while (left <= right) {
            const mid = Math.floor((left + right) / 2);
            const midValue = sortedList[mid];
            const currentDiff = Math.abs(midValue - target);
            minDiff = Math.min(minDiff, currentDiff);
            if (midValue < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }   

        }
        const insertIndex = left;
        sortedList.splice(insertIndex, 0, nums[i - x]);
    }
    return minDiff; 
};
