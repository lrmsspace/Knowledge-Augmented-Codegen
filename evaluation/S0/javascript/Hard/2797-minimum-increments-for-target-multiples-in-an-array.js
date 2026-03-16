// Source: https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays, nums and target.
//
// In a single operation, you may increment any element of nums by 1.
//
// Return the minimum number of operations required so that each element in target has at least one multiple in nums.
//
// Example:
// Input: nums = [1,2,3], target = [4]
//
// Output: 1
//
// Explanation:
//
// The minimum number of operations required to satisfy the condition is 1.
//
//
// 	Increment 3 to 4 with just one operation, making 4 a multiple of itself.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= target.length <= 4
// 	target.length <= nums.length
// 	1 <= nums[i], target[i] <= 104
//

/**
 * @param {number[]} nums
 * @param {number[]} target
 * @return {number}
 */
var minimumIncrements = function(nums, target) {
    const n = nums.length;
    const m = target.length;
    let increments = 0;
    const used = Array(m).fill(false);

    nums.sort((a, b) => a - b);
    target.sort((a, b) => a - b);               
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < m; j++) {
            if (!used[j] && nums[i] <= target[j]) {
                const remainder = nums[i] % target[j];
                const increment = remainder === 0 ? 0 : target[j] - remainder;
                increments += increment;
                used[j] = true;
                break;
            }
        }
    }
    return increments;                                  
};
