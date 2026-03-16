// Source: https://leetcode.com/problems/make-array-elements-equal-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// Start by selecting a starting position curr such that nums[curr] == 0, and choose a movement direction of either left or right.
//
// After that, you repeat the following process:
//
//
// 	If curr is out of the range [0, n - 1], this process ends.
// 	If nums[curr] == 0, move in the current direction by incrementing curr if you are moving right, or decrementing curr if you are moving left.
// 	Else if nums[curr] > 0:
// 	
// 		Decrement nums[curr] by 1.
// 		Reverse your movement direction (left becomes right and vice versa).
// 		Take a step in your new direction.
// 	
// 	
//
//
// A selection of the initial position curr and movement direction is considered valid if every element in nums becomes 0 by the end of the process.
//
// Return the number of possible valid selections.
//
// Example:
// Input: nums = [1,0,2,0,3]
//
// Output: 2
//
// Explanation:
//
// The only possible valid selections are the following:
//
//
// 	Choose curr = 3, and a movement direction to the left.
//
// 	
// 		[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,1,0,3] -> [1,0,1,0,3] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,0,0,2] -> [1,0,0,0,2] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,0].
// 	
// 	
// 	Choose curr = 3, and a movement direction to the right.
// 	
// 		[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,2,0,2] -> [1,0,2,0,2] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,1,0,1] -> [1,0,1,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [0,0,0,0,0].
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 100
// 	There is at least one element i where nums[i] == 0.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countValidSelections = function(nums) {
    const n = nums.length;
    let validSelections = 0;
    for (let start = 0; start < n; start++) {
        if (nums[start] !== 0) continue;
        for (const direction of [-1, 1]) {
            const arr = nums.slice();
            let curr = start;
            let dir = direction;
            while (curr >= 0 && curr < n) { 
                if (arr[curr] === 0) {
                    curr += dir;
                }
                else {
                    arr[curr]--;
                    dir = -dir;
                    curr += dir;
                }
            }
            if (arr.every(num => num === 0)) {
                validSelections++;
            }
        }
    }
    return validSelections;
};
