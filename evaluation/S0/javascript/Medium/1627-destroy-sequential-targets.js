// Source: https://leetcode.com/problems/destroy-sequential-targets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers, representing targets on a number line. You are also given an integer space.
//
// You have a machine which can destroy targets. Seeding the machine with some nums[i] allows it to destroy all targets with values that can be represented as nums[i] + c * space, where c is any non-negative integer. You want to destroy the maximum number of targets in nums.
//
// Return the minimum value of nums[i] you can seed the machine with to destroy the maximum number of targets.
//
// Example:
// Input: nums = [3,7,8,1,1,5], space = 2
// Output: 1
// Explanation: If we seed the machine with nums[3], then we destroy all targets equal to 1,3,5,7,9,... 
// In this case, we would destroy 5 total targets (all except for nums[2]). 
// It is impossible to destroy more than 5 targets, so we return nums[3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= space <= 109
//

/**
 * @param {number[]} nums
 * @param {number} space
 * @return {number}
 */
var destroyTargets = function(nums, space) {
    const remainderCount = new Map();
    const remainderMinNum = new Map();
    for (const num of nums) {
        const remainder = num % space;
        remainderCount.set(remainder, (remainderCount.get(remainder) || 0) + 1);
        if (!remainderMinNum.has(remainder) || num < remainderMinNum.get(remainder)) {
            remainderMinNum.set(remainder, num);
        }
    }
    let maxCount = 0;
    let result = Infinity;
    for (const [remainder, count] of remainderCount.entries()) {
        if (count > maxCount || (count === maxCount && remainderMinNum.get(remainder) < result)) {
            maxCount = count;
            result = remainderMinNum.get(remainder);
        }
    }
    return result;
};