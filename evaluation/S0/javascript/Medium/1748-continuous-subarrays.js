// Source: https://leetcode.com/problems/continuous-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:
//
//
// 	Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.
//
//
// Return the total number of continuous subarrays.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [5,4,2,4]
// Output: 8
// Explanation: 
// Continuous subarray of size 1: [5], [4], [2], [4].
// Continuous subarray of size 2: [5,4], [4,2], [2,4].
// Continuous subarray of size 3: [4,2,4].
// There are no subarrys of size 4.
// Total continuous subarrays = 4 + 3 + 1 = 8.
// It can be shown that there are no more continuous subarrays.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var continuousSubarrays = function(nums) {
    let left = 0;
    let result = 0;
    const minDeque = [];
    const maxDeque = [];
    for (let right = 0; right < nums.length; right++) {
        while (minDeque.length && nums[minDeque[minDeque.length - 1]] >= nums[right]) {
            minDeque.pop();
        }
        minDeque.push(right);
        while (maxDeque.length && nums[maxDeque[maxDeque.length - 1]] <= nums[right]) {
            maxDeque.pop();
        }
        maxDeque.push(right);

        while (nums[maxDeque[0]] - nums[minDeque[0]] > 2) {
            if (minDeque[0] === left) {
                minDeque.shift();
            }
            if (maxDeque[0] === left) {
                maxDeque.shift();
            }
            left++;
        }
        result += right - left + 1;
    }
    return result;  
};
