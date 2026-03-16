// Source: https://leetcode.com/problems/jump-game-vi/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// You are initially standing at index 0. In one move, you can jump at most k steps forward without going outside the boundaries of the array. That is, you can jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive.
//
// You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j] for each index j you visited in the array.
//
// Return the maximum score you can get.
//
// Example:
// Input: nums = [1,-1,-2,4,-7,3], k = 2
// Output: 7
// Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (underlined above). The sum is 7.
//
// Constraints:
// 1 <= nums.length, k <= 105
// 	-104 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxResult = function(nums, k) {
    const n = nums.length;
    const dp = Array(n).fill(0);
    dp[0] = nums[0];
    const deque = [];
    deque.push(0);
    for (let i = 1; i < n; i++) {
        while (deque.length > 0 && deque[0] < i - k) {
            deque.shift();
        }
        dp[i] = dp[deque[0]] + nums[i];
        while (deque.length > 0 && dp[i] >= dp[deque[deque.length - 1]]) {
            deque.pop();
        }
        deque.push(i);
    }
    return dp[n - 1];
};