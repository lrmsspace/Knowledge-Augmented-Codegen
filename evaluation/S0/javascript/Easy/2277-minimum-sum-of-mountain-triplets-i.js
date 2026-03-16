// Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of integers.
//
// A triplet of indices (i, j, k) is a mountain if:
//
//
// 	i < j < k
// 	nums[i] < nums[j] and nums[k] < nums[j]
//
//
// Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.
//
// Example:
// Input: nums = [8,6,1,5,3]
// Output: 9
// Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
// - 2 < 3 < 4
// - nums[2] < nums[3] and nums[4] < nums[3]
// And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
//
// Constraints:
// 3 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumSum = function(nums) {
    const n = nums.length;
    let minSum = Infinity;
    for (let i = 0; i < n - 2; i++) {
        for (let j = i + 1; j < n - 1; j++) {
            for (let k = j + 1; k < n; k++) {
                if (nums[i] < nums[j] && nums[k] < nums[j]) {
                    const sum = nums[i] + nums[j] + nums[k];
                    if (sum < minSum) {
                        minSum = sum;
                    }
                }
            }
        }
    }
    return minSum === Infinity ? -1 : minSum;
};