// Source: https://leetcode.com/problems/intersection-of-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.
//
// Example:
// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2]
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	0 <= nums1[i], nums2[i] <= 1000
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number[]}
 */
var intersection = function(nums1, nums2) {
    const set1 = new Set(nums1);
    const resultSet = new Set();
    for (const num of nums2) {
        if (set1.has(num)) {
            resultSet.add(num);
        }
    }
    return Array.from(resultSet);
};