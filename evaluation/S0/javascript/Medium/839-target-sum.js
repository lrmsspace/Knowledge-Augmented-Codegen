// Source: https://leetcode.com/problems/target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer target.
//
// You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.
//
//
// 	For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
//
//
// Return the number of different expressions that you can build, which evaluates to target.
//
// Example:
// Input: nums = [1,1,1,1,1], target = 3
// Output: 5
// Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3
//
// Constraints:
// 1 <= nums.length <= 20
// 	0 <= nums[i] <= 1000
// 	0 <= sum(nums[i]) <= 1000
// 	-1000 <= target <= 1000
//

/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var findTargetSumWays = function(nums, target) {
    const n = nums.length;
    const memo = new Map();
    const backtrack = (index, currentSum) => {
        if (index === n) {
            return currentSum === target ? 1 : 0;
        }
        const key = `${index},${currentSum}`;
        if (memo.has(key)) {
            return memo.get(key);
        }
        const add = backtrack(index + 1, currentSum + nums[index]);
        const subtract = backtrack(index + 1, currentSum - nums[index]);
        const totalWays = add + subtract;
        memo.set(key, totalWays);
        return totalWays;
    };
    return backtrack(0, 0);
};
