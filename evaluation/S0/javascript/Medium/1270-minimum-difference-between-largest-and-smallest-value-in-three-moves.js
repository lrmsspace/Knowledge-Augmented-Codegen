// Source: https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// In one move, you can choose one element of nums and change it to any value.
//
// Return the minimum difference between the largest and smallest value of nums after performing at most three moves.
//
// Example:
// Input: nums = [5,3,2,4]
// Output: 0
// Explanation: We can make at most 3 moves.
// In the first move, change 2 to 3. nums becomes [5,3,3,4].
// In the second move, change 4 to 3. nums becomes [5,3,3,3].
// In the third move, change 5 to 3. nums becomes [3,3,3,3].
// After performing 3 moves, the difference between the minimum and maximum is 3 - 3 = 0.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minDifference = function(nums) {
    const n = nums.length;
    if (n <= 4) return 0;
    nums.sort((a, b) => a - b);
    let minDiff = Infinity;
    for (let i = 0; i <= 3; i++) {
        minDiff = Math.min(minDiff, nums[n - 4 + i] - nums[i]);
    }
    return minDiff;
};
