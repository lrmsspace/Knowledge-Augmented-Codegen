// Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// The distinct count of a subarray of nums is defined as:
//
//
// 	Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
//
//
// Return the sum of the squares of distinct counts of all subarrays of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,1]
// Output: 15
// Explanation: Six possible subarrays are:
// [1]: 1 distinct value
// [2]: 1 distinct value
// [1]: 1 distinct value
// [1,2]: 2 distinct values
// [2,1]: 2 distinct values
// [1,2,1]: 2 distinct values
// The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumCounts = function(nums) {
    const mod = 1e9 + 7;
    const n = nums.length;
    const countMap = new Map();
    let left = 0;
    let sum = 0;
    let result = 0;
    for (let right = 0; right < n; right++) {
        const num = nums[right];
        countMap.set(num, (countMap.get(num) || 0) + 1);
        while (countMap.get(num) > 1) {
            const leftNum = nums[left];
            countMap.set(leftNum, countMap.get(leftNum) - 1);
            if (countMap.get(leftNum) === 0) {
                countMap.delete(leftNum);
            }
            left++;
        }
        const distinctCount = countMap.size;
        sum = (sum + distinctCount * distinctCount) % mod;
    }
    return sum;
};
