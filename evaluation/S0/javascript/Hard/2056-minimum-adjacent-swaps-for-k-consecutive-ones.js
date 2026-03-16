// Source: https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.
//
// Return the minimum number of moves required so that nums has k consecutive 1's.
//
// Example:
// Input: nums = [1,0,0,1,0,1], k = 2
// Output: 1
// Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is 0 or 1.
// 	1 <= k <= sum(nums)
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minMoves = function(nums, k) {
    const onesPositions = [];
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] === 1) {
            onesPositions.push(i);
        }
    }
    const prefixSums = new Array(onesPositions.length + 1).fill(0);
    for (let i = 0; i < onesPositions.length; i++) {
        prefixSums[i + 1] = prefixSums[i] + onesPositions[i];
    }

    let minMoves = Infinity;
    for (let i = 0; i <= onesPositions.length - k; i++) {
        const mid = i + Math.floor(k / 2);
        const median = onesPositions[mid];
        const leftSum = prefixSums[mid] - prefixSums[i];
        const rightSum = prefixSums[i + k] - prefixSums[mid + 1];
        const leftCount = mid - i;
        const rightCount = i + k - mid - 1;
        const moves = (median * leftCount - leftSum) + (rightSum - median * rightCount);
        minMoves = Math.min(minMoves, moves);
    }

    return minMoves;
};
