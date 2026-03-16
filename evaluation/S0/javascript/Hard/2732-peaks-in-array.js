// Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
//
// Problem Description:
// A peak in an array arr is an element that is greater than its previous and next element in arr.
//
// You are given an integer array nums and a 2D integer array queries.
//
// You have to process queries of two types:
//
//
// 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
// 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
//
// Output: [0]
//
// Explanation:
//
// First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
//
// Second query: The number of peaks in the [3,1,4,4,5] is 0.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i][0] == 1 or queries[i][0] == 2
// 	For all i that:
// 	
// 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
// 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
var countOfPeaks = function(nums, queries) {
    const n = nums.length;
    const peaks = new Array(n).fill(0);
    for (let i = 1; i < n - 1; i++) {
        if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
            peaks[i] = 1;
        }
    }
    const prefixSum = new Array(n).fill(0);
    for (let i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + peaks[i];
    }
    const result = [];
    for (const query of queries) {
        const [type, x, y] = query;
        if (type === 1) {
            result.push(prefixSum[y] - prefixSum[x]);
        }
        else {
            nums[x] = y;
            for (let i = Math.max(1, x - 1); i <= Math.min(n - 2, x + 1); i++) {
                peaks[i] = (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) ? 1 : 0;
            }
            for (let i = Math.max(1, x - 1); i <= Math.min(n - 2, x + 1); i++) {
                prefixSum[i] = prefixSum[i - 1] + peaks[i];
            }
        }
    }
    return result;
};
