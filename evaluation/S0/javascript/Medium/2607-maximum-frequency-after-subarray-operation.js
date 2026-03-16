// Source: https://leetcode.com/problems/maximum-frequency-after-subarray-operation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of length n. You are also given an integer k.
//
// You perform the following operation on nums once:
//
//
// 	Select a subarray nums[i..j] where 0 <= i <= j <= n - 1.
// 	Select an integer x and add x to all the elements in nums[i..j].
//
//
// Find the maximum frequency of the value k after the operation.
//
// Example:
// Input: nums = [1,2,3,4,5,6], k = 1
//
// Output: 2
//
// Explanation:
//
// After adding -5 to nums[2..5], 1 has a frequency of 2 in [1, 2, -2, -1, 0, 1].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 50
// 	1 <= k <= 50
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxFrequency = function(nums, k) {
    const freq = new Array(51).fill(0);
    for (const num of nums) {
        freq[num]++;
    }
    let maxFreq = 0;
    for (let i = 1; i <= 50; i++) {
        if (freq[i] > 0) {
            const diff = Math.abs(i - k);
            if (diff <= k) {
                maxFreq = Math.max(maxFreq, freq[i]);
            }
        }
    }
    return maxFreq; 
};
