// Source: https://leetcode.com/problems/count-beautiful-splits-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums.
//
// A split of an array nums is beautiful if:
//
//
// 	The array nums is split into three subarrays: nums1, nums2, and nums3, such that nums can be formed by concatenating nums1, nums2, and nums3 in that order.
// 	The subarray nums1 is a prefix of nums2 OR nums2 is a prefix of nums3.
//
//
// Return the number of ways you can make this split.
//
// Example:
// Input: nums = [1,1,2,1]
//
// Output: 2
//
// Explanation:
//
// The beautiful splits are:
//
//
// 	A split with nums1 = [1], nums2 = [1,2], nums3 = [1].
// 	A split with nums1 = [1], nums2 = [1], nums3 = [2,1].
//
// Constraints:
// 1 <= nums.length <= 5000
// 	0 <= nums[i] <= 50
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var beautifulSplits = function(nums) {
    const count = new Array(51).fill(0);
    for (const num of nums) {
        count[num]++;
    }
    let totalSplits = 0;
    let prefixCount = 0;
    for (let i = 0; i < 51; i++) {
        if (count[i] > 0) {
            totalSplits += prefixCount * (count[i] + prefixCount);
            prefixCount += count[i];
        }
    }
    return totalSplits; 
};
