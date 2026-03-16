// Source: https://leetcode.com/problems/append-k-integers-with-minimal-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Append k unique positive integers that do not appear in nums to nums such that the resulting total sum is minimum.
//
// Return the sum of the k integers appended to nums.
//
// Example:
// Input: nums = [1,4,25,10,25], k = 2
// Output: 5
// Explanation: The two unique positive integers that do not appear in nums which we append are 2 and 3.
// The resulting sum of nums is 1 + 4 + 25 + 10 + 25 + 2 + 3 = 70, which is the minimum.
// The sum of the two integers appended is 2 + 3 = 5, so we return 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 108
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var minimalKSum = function(nums, k) {
    nums = Array.from(new Set(nums));
    nums.sort((a, b) => a - b);
    let totalSum = 0;
    let current = 1;
    for (const num of nums) {
        if (num > current) {
            const end = Math.min(num - 1, current + k - 1);
            const count = end - current + 1;
            totalSum += ((current + end) * count) / 2;
            k -= count;
            if (k === 0) {
                return totalSum;
            }
        }
        current = num + 1;
    }
    if (k > 0) {
        const end = current + k - 1;
        totalSum += ((current + end) * k) / 2;
    }
    return totalSum;
};
