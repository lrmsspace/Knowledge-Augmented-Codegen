// Source: https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums​​​ and an integer k​​​​​. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
//
// Return the minimum number of elements to change in the array such that the XOR of all segments of size k​​​​​​ is equal to zero.
//
// Example:
// Input: nums = [1,2,0,3,0], k = 1
// Output: 3
// Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
//
// Constraints:
// 1 <= k <= nums.length <= 2000
// 	​​​​​​0 <= nums[i] < 210
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minChanges = function(nums, k) {
    const n = nums.length;
    const freq = Array.from({ length: k }, () => new Map());
    for (let i = 0; i < n; i++) {
        const mod = i % k;
        freq[mod].set(nums[i], (freq[mod].get(nums[i]) || 0) + 1);
    }
    const dp = new Array(1 << 10).fill(Infinity);
    dp[0] = 0;
    for (let i = 0; i < k; i++) {
        const newDp = new Array(1 << 10).fill(Infinity);
        for (let mask = 0; mask < (1 << 10); mask++) {
            if (dp[mask] === Infinity) continue;
            for (const [num, count] of freq[i]) {
                const newMask = mask ^ num;
                newDp[newMask] = Math.min(newDp[newMask], dp[mask] + freq[i].size - count);
            }
        }
        for (let mask = 0; mask < (1 << 10); mask++) {
            dp[mask] = newDp[mask];
        }
    }
    return dp[0];   
};
