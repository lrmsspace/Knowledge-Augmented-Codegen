// Source: https://leetcode.com/problems/zero-array-transformation-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].
//
// Each queries[i] represents the following action on nums:
//
//
// 	Decrement the value at each index in the range [li, ri] in nums by at most vali.
// 	The amount by which each value is decremented can be chosen independently for each index.
//
//
// A Zero Array is an array with all its elements equal to 0.
//
// Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
//
// Example:
// Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
//
// Output: 2
//
// Explanation:
//
//
// 	For i = 0 (l = 0, r = 2, val = 1):
//
// 	
// 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
// 		The array will become [1, 0, 1].
// 	
// 	
// 	For i = 1 (l = 0, r = 2, val = 1):
// 	
// 		Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
// 		The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 5 * 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 3
// 	0 <= li <= ri < nums.length
// 	1 <= vali <= 5
//

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number}
 */
var minZeroArray = function(nums, queries) {
    const n = nums.length;
    const diff = Array(n + 1).fill(0);
    for (const [l, r, val] of queries) {
        diff[l] -= val;
        diff[r + 1] += val;
    }
    let current = 0;
    for (let i = 0; i < n; i++) {
        current += diff[i];
        if (nums[i] + current > 0) {
            return -1;
        }
    }
    return queries.length;  
};
