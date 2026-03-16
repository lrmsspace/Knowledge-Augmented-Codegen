// Source: https://leetcode.com/problems/two-out-of-three/   |   Difficulty: Easy
//
// Problem Description:
// Given three integer arrays nums1, nums2, and nums3, return a distinct array containing all the values that are present in at least two out of the three arrays. You may return the values in any order.
//
// Example:
// Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
// Output: [3,2]
// Explanation: The values that are present in at least two arrays are:
// - 3, in all three arrays.
// - 2, in nums1 and nums2.
//
// Constraints:
// 1 <= nums1.length, nums2.length, nums3.length <= 100
// 	1 <= nums1[i], nums2[j], nums3[k] <= 100
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number[]} nums3
 * @return {number[]}
 */
var twoOutOfThree = function(nums1, nums2, nums3) {
    const countMap = new Map();
    const arrays = [nums1, nums2, nums3];
    for (const arr of arrays) {
        const uniqueNums = new Set(arr);
        for (const num of uniqueNums) {
            countMap.set(num, (countMap.get(num) || 0) + 1);
        }
    }
    const result = [];
    for (const [num, count] of countMap.entries()) {
        if (count >= 2) {
            result.push(num);
        }
    }
    return result;
};