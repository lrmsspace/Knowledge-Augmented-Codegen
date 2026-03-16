// Source: https://leetcode.com/problems/ways-to-make-a-fair-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element. Notice that the index of the elements may change after the removal.
//
// For example, if nums = [6,1,7,4,1]:
//
//
// 	Choosing to remove index 1 results in nums = [6,7,4,1].
// 	Choosing to remove index 2 results in nums = [6,1,4,1].
// 	Choosing to remove index 4 results in nums = [6,1,7,4].
//
//
// An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.
//
// Return the number of indices that you could choose such that after the removal, nums is fair.
//
// Example:
// Input: nums = [2,1,6,4]
// Output: 1
// Explanation:
// Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
// Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
// Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
// Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
// There is 1 index that you can remove to make nums fair.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var waysToMakeFair = function(nums) {
    const n = nums.length;      
    const prefixEven = Array(n + 1).fill(0);
    const prefixOdd = Array(n + 1).fill(0);
    
    for (let i = 0; i < n; i++) {
        prefixEven[i + 1] = prefixEven[i];
        prefixOdd[i + 1] = prefixOdd[i];
        if (i % 2 === 0) {
            prefixEven[i + 1] += nums[i];
        }
        else {
            prefixOdd[i + 1] += nums[i];
        }
    }
    
    let count = 0;
    for (let i = 0; i < n; i++) {
        const evenSum = prefixEven[i] + (prefixOdd[n] - prefixOdd[i + 1]);
        const oddSum = prefixOdd[i] + (prefixEven[n] - prefixEven[i + 1]);
        if (evenSum === oddSum) {
            count++;
        }
    }
    return count;
};