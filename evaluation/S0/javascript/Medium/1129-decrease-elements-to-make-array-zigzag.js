// Source: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
//
// An array A is a zigzag array if either:
//
//
//  Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
//  OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
//
//
// Return the minimum number of moves to transform the given array nums into a zigzag array.
//
// Example:
// Input: nums = [1,2,3]
// Output: 2
// Explanation: We can decrease 2 to 0 or 3 to 1.
//
// Constraints:
// 1 <= nums.length <= 1000
//  1 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var movesToMakeZigzag = function(nums) {
    const n = nums.length;
    let evenMoves = 0;
    let oddMoves = 0;
    for (let i = 0; i < n; i++) {
        let left = i > 0 ? nums[i - 1] : Infinity;
        let right = i < n - 1 ? nums[i + 1] : Infinity;
        if (i % 2 === 0) {
            if (nums[i] >= Math.min(left, right)) {
                evenMoves += nums[i] - Math.min(left, right) + 1;
            }
        } else {
            if (nums[i] >= Math.min(left, right)) {
                oddMoves += nums[i] - Math.min(left, right) + 1;
            }
        }
    }
    return Math.min(evenMoves, oddMoves);
        
};
