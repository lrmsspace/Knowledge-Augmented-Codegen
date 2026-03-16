// Source: https://leetcode.com/problems/ant-on-the-boundary/   |   Difficulty: Easy
//
// Problem Description:
// An ant is on a boundary. It sometimes goes left and sometimes right.
//
// You are given an array of non-zero integers nums. The ant starts reading nums from the first element of it to its end. At each step, it moves according to the value of the current element:
//
//
// 	If nums[i] < 0, it moves left by -nums[i] units.
// 	If nums[i] > 0, it moves right by nums[i] units.
//
//
// Return the number of times the ant returns to the boundary.
//
// Example:
// Input: nums = [2,3,-5]
// Output: 1
// Explanation: After the first step, the ant is 2 steps to the right of the boundary.
// After the second step, the ant is 5 steps to the right of the boundary.
// After the third step, the ant is on the boundary.
// So the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-10 <= nums[i] <= 10
// 	nums[i] != 0
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var returnToBoundaryCount = function(nums) {
    let position = 0;
    let returnCount = 0;
    for (const step of nums) {
        position += step;
        if (position === 0) {
            returnCount++;
        }
    }
    return returnCount;
};