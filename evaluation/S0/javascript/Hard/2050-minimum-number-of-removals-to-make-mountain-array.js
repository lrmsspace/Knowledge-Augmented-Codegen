// Source: https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/   |   Difficulty: Hard
//
// Problem Description:
// You may recall that an array arr is a mountain array if and only if:
//
//
// 	arr.length >= 3
// 	There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
// 	
// 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
// 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
// 	
// 	
//
//
// Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.
//
// Example:
// Input: nums = [1,3,1]
// Output: 0
// Explanation: The array itself is a mountain array so we do not need to remove any elements.
//
// Constraints:
// 3 <= nums.length <= 1000
// 	1 <= nums[i] <= 109
// 	It is guaranteed that you can make a mountain array out of nums.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumMountainRemovals = function(nums) {
    const n = nums.length;
    const left = new Array(n).fill(1);
    const right = new Array(n).fill(1);
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                left[i] = Math.max(left[i], left[j] + 1);
            }
        }
    }
    for (let i = n - 1; i >= 0; i--) {
        for (let j = n - 1; j > i; j--) {
            if (nums[i] > nums[j]) {
                right[i] = Math.max(right[i], right[j] + 1);
            }
        }
    }
    let maxMountainLength = 0;
    for (let i = 0; i < n; i++) {
        if (left[i] > 1 && right[i] > 1) {
            maxMountainLength = Math.max(maxMountainLength, left[i] + right[i] - 1);
        }
    }
    return n - maxMountainLength;   
};
