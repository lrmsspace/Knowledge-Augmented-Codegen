// Source: https://leetcode.com/problems/count-of-range-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive.
//
// Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.
//
// Example:
// Input: nums = [-2,5,-1], lower = -2, upper = 2
// Output: 3
// Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
// 	-105 <= lower <= upper <= 105
// 	The answer is guaranteed to fit in a 32-bit integer.
//

/**
 * @param {number[]} nums
 * @param {number} lower
 * @param {number} upper
 * @return {number}
 */
var countRangeSum = function(nums, lower, upper) {
    const prefixSums = [0];
    for (let num of nums) {
        prefixSums.push(prefixSums[prefixSums.length - 1] + num);
    }   
    const sortedPrefixSums = [];
    let count = 0;
    for (let sum of prefixSums) {
        const left = binarySearch(sortedPrefixSums, sum - upper);
        const right = binarySearch(sortedPrefixSums, sum - lower + 1);
        count += right - left;
        sortedPrefixSums.splice(binarySearch(sortedPrefixSums, sum), 0, sum);
    }
    return count;   
};
