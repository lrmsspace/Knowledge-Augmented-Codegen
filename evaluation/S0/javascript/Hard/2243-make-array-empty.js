// Source: https://leetcode.com/problems/make-array-empty/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums containing distinct numbers, and you can perform the following operations until the array is empty:
//
//
// 	If the first element has the smallest value, remove it
// 	Otherwise, put the first element at the end of the array.
//
//
// Return an integer denoting the number of operations it takes to make nums empty.
//
// Example:
// Input: nums = [3,4,-1]
// Output: 5
//
//
//
// 	
// 		
// 			Operation
// 			Array
// 		
// 	
// 	
// 		
// 			1
// 			[4, -1, 3]
// 		
// 		
// 			2
// 			[-1, 3, 4]
// 		
// 		
// 			3
// 			[3, 4]
// 		
// 		
// 			4
// 			[4]
// 		
// 		
// 			5
// 			[]
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	All values in nums are distinct.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var countOperationsToEmptyArray = function(nums) {
    const n = nums.length;
    const sorted = [...nums].sort((a, b) => a - b);
    const indexMap = new Map();
    for (let i = 0; i < n; i++) {
        indexMap.set(sorted[i], i);
    }
    let operations = 0;
    for (let i = 0; i < n; i++) {
        const index = indexMap.get(nums[i]);
        operations += (index - i + n) % n;
    }
    return operations;
        
};
