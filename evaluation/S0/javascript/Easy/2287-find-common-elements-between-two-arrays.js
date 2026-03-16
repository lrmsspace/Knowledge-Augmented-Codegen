// Source: https://leetcode.com/problems/find-common-elements-between-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of sizes n and m, respectively. Calculate the following values:
//
//
// 	answer1 : the number of indices i such that nums1[i] exists in nums2.
// 	answer2 : the number of indices i such that nums2[i] exists in nums1.
//
//
// Return [answer1,answer2].
//
// Example:
// Input: nums1 = [2,3,2], nums2 = [1,2]
//
// Output: [2,1]
//
// Explanation:
//
// Constraints:
// n == nums1.length
// 	m == nums2.length
// 	1 <= n, m <= 100
// 	1 <= nums1[i], nums2[i] <= 100
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number[]}
 */
var findIntersectionValues = function(nums1, nums2) {
    const set1 = new Set(nums1);
    const set2 = new Set(nums2);
    let answer1 = 0;
    let answer2 = 0;
    for (let i = 0; i < nums1.length; i++) {
        if (set2.has(nums1[i])) {
            answer1++;
        }
    }
    for (let i = 0; i < nums2.length; i++) {
        if (set1.has(nums2[i])) {
            answer2++;
        }
    }
    return [answer1, answer2];
};