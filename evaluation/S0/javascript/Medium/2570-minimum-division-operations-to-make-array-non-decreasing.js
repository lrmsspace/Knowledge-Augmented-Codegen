// Source: https://leetcode.com/problems/minimum-division-operations-to-make-array-non-decreasing/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// Any positive divisor of a natural number x that is strictly less than x is called a proper divisor of x. For example, 2 is a proper divisor of 4, while 6 is not a proper divisor of 6.
//
// You are allowed to perform an operation any number of times on nums, where in each operation you select any one element from nums and divide it by its greatest proper divisor.
//
// Return the minimum number of operations required to make the array non-decreasing.
//
// If it is not possible to make the array non-decreasing using any number of operations, return -1.
//
// Example:
// Input: nums = [25,7]
//
// Output: 1
//
// Explanation:
//
// Using a single operation, 25 gets divided by 5 and nums becomes [5, 7].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minOperations = function(nums) {
    const n = nums.length;
    let operations = 0;
    for (let i = n - 2; i >= 0; i--) {
        while (nums[i] > nums[i + 1]) {
            const divisor = greatestProperDivisor(nums[i]);
            if (divisor === 1) {
                return -1;
            }
            nums[i] = Math.floor(nums[i] / divisor);
            operations++;
        }
    }
    return operations;  
};
