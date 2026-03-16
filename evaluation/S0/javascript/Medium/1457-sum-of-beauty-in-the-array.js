// Source: https://leetcode.com/problems/sum-of-beauty-in-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. For each index i (1 <= i <= nums.length - 2) the beauty of nums[i] equals:
//
//
// 	2, if nums[j] < nums[i] < nums[k], for all 0 <= j < i and for all i < k <= nums.length - 1.
// 	1, if nums[i - 1] < nums[i] < nums[i + 1], and the previous condition is not satisfied.
// 	0, if none of the previous conditions holds.
//
//
// Return the sum of beauty of all nums[i] where 1 <= i <= nums.length - 2.
//
// Example:
// Input: nums = [1,2,3]
// Output: 2
// Explanation: For each index i in the range 1 <= i <= 1:
// - The beauty of nums[1] equals 2.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumOfBeauties = function(nums) {
    const n = nums.length;  
    let leftMax = new Array(n).fill(0);
    let rightMin = new Array(n).fill(0);
    let sumBeauty = 0;

    leftMax[0] = nums[0];
    for (let i = 1; i < n; i++) {
        leftMax[i] = Math.max(leftMax[i - 1], nums[i]);
    }
        
    rightMin[n - 1] = nums[n - 1];
    for (let i = n - 2; i >= 0; i--) {
        rightMin[i] = Math.min(rightMin[i + 1], nums[i]);
    }
    for (let i = 1; i < n - 1; i++) {
        if (leftMax[i - 1] < nums[i] && nums[i] < rightMin[i + 1]) {
            sumBeauty += 2;
        } else if (nums[i - 1] < nums[i] && nums[i] < nums[i + 1]) {
            sumBeauty += 1;
        }
    }
    return sumBeauty;
    
};
