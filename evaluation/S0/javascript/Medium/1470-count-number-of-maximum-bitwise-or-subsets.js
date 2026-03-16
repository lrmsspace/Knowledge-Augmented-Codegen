// Source: https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.
//
// An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.
//
// The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).
//
// Example:
// Input: nums = [3,1]
// Output: 2
// Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
// - [3]
// - [3,1]
//
// Constraints:
// 1 <= nums.length <= 16
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countMaxOrSubsets = function(nums) {
    const n = nums.length;
    let maxOr = 0;
    let count = 0;

    const dfs = (index, currentOr) => {
        if (index === n) {
            if (currentOr > maxOr) {
                maxOr = currentOr;
                count = 1;
            } else if (currentOr === maxOr) {
                count++;
            }
            return;
        }

        // Include nums[index]
        dfs(index + 1, currentOr | nums[index]);
        // Exclude nums[index]
        dfs(index + 1, currentOr);
    };

    dfs(0, 0);
    return count;
};