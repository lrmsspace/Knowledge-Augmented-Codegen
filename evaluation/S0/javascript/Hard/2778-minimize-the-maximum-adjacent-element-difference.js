// Source: https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums. Some values in nums are missing and are denoted by -1.
//
// You must choose a pair of positive integers (x, y) exactly once and replace each missing element with either x or y.
//
// You need to minimize the maximum absolute difference between adjacent elements of nums after replacements.
//
// Return the minimum possible difference.
//
// Example:
// Input: nums = [1,2,-1,10,8]
//
// Output: 4
//
// Explanation:
//
// By choosing the pair as (6, 7), nums can be changed to [1, 2, 6, 10, 8].
//
// The absolute differences between adjacent elements are:
//
//
// 	|1 - 2| == 1
// 	|2 - 6| == 4
// 	|6 - 10| == 4
// 	|10 - 8| == 2
//
// Constraints:
// 2 <= nums.length <= 105
// 	nums[i] is either -1 or in the range [1, 109].
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minDifference = function(nums) {
    let left = -1;
    let right = -1;
    let maxDiff = 0;
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] !== -1) {
            if (left !== -1) {
                maxDiff = Math.max(maxDiff, Math.abs(nums[i] - nums[left]));
            }
            left = i;
        }
    }
    for (let i = nums.length - 1; i >= 0; i--) {
        if (nums[i] !== -1) {
            if (right !== -1) {
                maxDiff = Math.max(maxDiff, Math.abs(nums[i] - nums[right]));
            }
            right = i;
        }
    }
    let low = 1;
    let high = 1e9;
    while (low < high) {
        const mid = Math.floor((low + high) / 2);
        let prev = -1;
        let canAchieve = true;
        for (let i = 0; i < nums.length; i++) {
            if (nums[i] !== -1) {
                if (prev !== -1 && Math.abs(nums[i] - nums[prev]) > mid) {
                    canAchieve = false;
                    break;
                }
                prev = i;
            }
        }
        if (canAchieve) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return Math.max(low, maxDiff);  
};
