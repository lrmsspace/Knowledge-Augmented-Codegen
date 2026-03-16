// Source: https://leetcode.com/problems/sum-of-good-numbers/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums and an integer k, an element nums[i] is considered good if it is strictly greater than the elements at indices i - k and i + k (if those indices exist). If neither of these indices exists, nums[i] is still considered good.
//
// Return the sum of all the good elements in the array.
//
// Example:
// Input: nums = [1,3,2,1,5,4], k = 2
//
// Output: 12
//
// Explanation:
//
// The good numbers are nums[1] = 3, nums[4] = 5, and nums[5] = 4 because they are strictly greater than the numbers at indices i - k and i + k.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
// 	1 <= k <= floor(nums.length / 2)
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var sumOfGoodNumbers = function(nums, k) {
    let sum = 0;
    const n = nums.length;
    for (let i = 0; i < n; i++) {
        const leftIndex = i - k;
        const rightIndex = i + k;
        const leftValue = leftIndex >= 0 ? nums[leftIndex] : -Infinity;
        const rightValue = rightIndex < n ? nums[rightIndex] : -Infinity;
        if (nums[i] > leftValue && nums[i] > rightValue) {
            sum += nums[i];
        }
    }    return sum;    
};
