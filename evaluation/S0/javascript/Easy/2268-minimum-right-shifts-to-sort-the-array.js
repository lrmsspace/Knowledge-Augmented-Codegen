// Source: https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of length n containing distinct positive integers. Return the minimum number of right shifts required to sort nums and -1 if this is not possible.
//
// A right shift is defined as shifting the element at index i to index (i + 1) % n, for all indices.
//
// Example:
// Input: nums = [3,4,5,1,2]
// Output: 2
// Explanation: 
// After the first right shift, nums = [2,3,4,5,1].
// After the second right shift, nums = [1,2,3,4,5].
// Now nums is sorted; therefore the answer is 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	nums contains distinct integers.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumRightShifts = function(nums) {
    const n = nums.length;
    let pivotIndex = -1;
    for (let i = 1; i < n; i++) {
        if (nums[i] < nums[i - 1]) {
            pivotIndex = i;
            break;
        }
    }
    if (pivotIndex === -1) {
        return 0; // Already sorted
    }
    for (let i = pivotIndex + 1; i < n; i++) {
        if (nums[i] < nums[i - 1]) {
            return -1; // More than one pivot found
        }
    }
    if (nums[0] < nums[n - 1]) {
        return -1; // Not sorted after rotation
    }
    return n - pivotIndex;
};
