// Source: https://leetcode.com/problems/identify-the-largest-outlier-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. This array contains n elements, where exactly n - 2 elements are special numbers. One of the remaining two elements is the sum of these special numbers, and the other is an outlier.
//
// An outlier is defined as a number that is neither one of the original special numbers nor the element representing the sum of those numbers.
//
// Note that special numbers, the sum element, and the outlier must have distinct indices, but may share the same value.
//
// Return the largest potential outlier in nums.
//
// Example:
// Input: nums = [2,3,5,10]
//
// Output: 10
//
// Explanation:
//
// The special numbers could be 2 and 3, thus making their sum 5 and the outlier 10.
//
// Constraints:
// 3 <= nums.length <= 105
// 	-1000 <= nums[i] <= 1000
// 	The input is generated such that at least one potential outlier exists in nums.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var getLargestOutlier = function(nums) {
    const sum = nums.reduce((acc, num) => acc + num, 0);
    const maxNum = Math.max(...nums);
    return sum - maxNum > maxNum ? maxNum : sum - maxNum;   
};
