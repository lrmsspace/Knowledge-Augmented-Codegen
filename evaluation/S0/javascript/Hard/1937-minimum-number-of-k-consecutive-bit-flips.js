// Source: https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary array nums and an integer k.
//
// A k-bit flip is choosing a subarray of length k from nums and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
//
// Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is not possible, return -1.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [0,1,0], k = 1
// Output: 2
// Explanation: Flip nums[0], then flip nums[2].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minKBitFlips = function(nums, k) {
    const n = nums.length;
    const flip = new Array(n).fill(0);
    let flips = 0;
    let result = 0;
    for (let i = 0; i < n; i++) {
        flips ^= flip[i];
        if ((nums[i] ^ flips) === 0) {
            if (i + k > n) {
                return -1;
            }
            result++;
            flips ^= 1;
            if (i + k < n) {
                flip[i + k] = 1;
            }
        }
    }
    return result;
};
