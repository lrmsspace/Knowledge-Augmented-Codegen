// Source: https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k. You can perform the following operation any number of times:
//
//
// 	Select an index i and replace nums[i] with nums[i] - 1.
//
//
// Return the minimum number of operations required to make the sum of the array divisible by k.
//
// Example:
// Input: nums = [3,9,7], k = 5
//
// Output: 4
//
// Explanation:
//
//
// 	Perform 4 operations on nums[1] = 9. Now, nums = [3, 5, 7].
// 	The sum is 15, which is divisible by 5.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	1 <= k <= 100
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minOperations = function(nums, k) {
    const totalSum = nums.reduce((acc, num) => acc + num, 0);
    const remainder = totalSum % k;
    return remainder === 0 ? 0 : remainder; 
};
