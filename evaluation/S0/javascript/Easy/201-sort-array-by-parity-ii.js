// Source: https://leetcode.com/problems/sort-array-by-parity-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums, half of the integers in nums are odd, and the other half are even.
//
// Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.
//
// Return any answer array that satisfies this condition.
//
// Example:
// Input: nums = [4,2,5,7]
// Output: [4,5,2,7]
// Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
//
// Constraints:
// 2 <= nums.length <= 2 * 104
// 	nums.length is even.
// 	Half of the integers in nums are even.
// 	0 <= nums[i] <= 1000
//
//
//  
// Follow Up: Could you solve it in-place?
//

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var sortArrayByParityII = function(nums) {
    const n = nums.length;  
    const result = new Array(n);  
    let evenIndex = 0;  
    let oddIndex = 1;
    for (let i = 0; i < n; i++) {
        if (nums[i] % 2 === 0) {  
            result[evenIndex] = nums[i];
            evenIndex += 2;  
        } else {  
            result[oddIndex] = nums[i];
            oddIndex += 2;  
        }
    }
    return result;    
};
