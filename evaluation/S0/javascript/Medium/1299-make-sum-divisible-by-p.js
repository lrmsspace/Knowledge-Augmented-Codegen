// Source: https://leetcode.com/problems/make-sum-divisible-by-p/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
//
// Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
//
// A subarray is defined as a contiguous block of elements in the array.
//
// Example:
// Input: nums = [3,1,4,2], p = 6
// Output: 1
// Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= p <= 109
//

/**
 * @param {number[]} nums
 * @param {number} p
 * @return {number}
 */
var minSubarray = function(nums, p) {
    const totalMod = nums.reduce((acc, num) => (acc + num) % p, 0);
    if (totalMod === 0) return 0;
    const modIndexMap = new Map();
    modIndexMap.set(0, -1);
    let currentMod = 0;
    let minLength = nums.length;
    for (let i = 0; i < nums.length; i++) {
        currentMod = (currentMod + nums[i]) % p;
        const targetMod = (currentMod - totalMod + p) % p;
        if (modIndexMap.has(targetMod)) {
            const prevIndex = modIndexMap.get(targetMod);
            minLength = Math.min(minLength, i - prevIndex);
        }
        modIndexMap.set(currentMod, i);
    }
    return minLength === nums.length ? -1 : minLength;  
};
