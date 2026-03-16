// Source: https://leetcode.com/problems/zero-array-transformation-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri].
//
// Each queries[i] represents the following action on nums:
//
//
// 	Decrement the value at each index in the range [li, ri] in nums by at most 1.
// 	The amount by which the value is decremented can be chosen independently for each index.
//
//
// A Zero Array is an array with all its elements equal to 0.
//
// Return the maximum number of elements that can be removed from queries, such that nums can still be converted to a zero array using the remaining queries. If it is not possible to convert nums to a zero array, return -1.
//
// Example:
// Input: nums = [2,0,2], queries = [[0,2],[0,2],[1,1]]
//
// Output: 1
//
// Explanation:
//
// After removing queries[2], nums can still be converted to a zero array.
//
//
// 	Using queries[0], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
// 	Using queries[1], decrement nums[0] and nums[2] by 1 and nums[1] by 0.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= li <= ri < nums.length
//

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number}
 */
var maxRemoval = function(nums, queries) {
    const n = nums.length;
    const diff = Array(n + 1).fill(0);  
    for (const [l, r] of queries) {
        diff[l]--;
        diff[r + 1]++;
    }
    let current = 0;
    let removals = 0;
    for (let i = 0; i < n; i++) {
        current += diff[i];
        if (nums[i] + current < 0) {
            return -1; 
        }
        if (nums[i] + current === 0) {
            removals++;
        }
    }
    return removals;    
};
