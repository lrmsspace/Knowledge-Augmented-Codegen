// Source: https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/   |   Difficulty: Medium
//
// Problem Description:
// You are given two non-increasing 0-indexed integer arrays nums1​​​​​​ and nums2​​​​​​.
//
// A pair of indices (i, j), where 0 <= i < nums1.length and 0 <= j < nums2.length, is valid if both i <= j and nums1[i] <= nums2[j]. The distance of the pair is j - i​​​​.
//
// Return the maximum distance of any valid pair (i, j). If there are no valid pairs, return 0.
//
// An array arr is non-increasing if arr[i-1] >= arr[i] for every 1 <= i < arr.length.
//
// Example:
// Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
// Output: 2
// Explanation: The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4), and (4,4).
// The maximum distance is 2 with pair (2,4).
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	1 <= nums1[i], nums2[j] <= 105
// 	Both nums1 and nums2 are non-increasing.
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var maxDistance = function(nums1, nums2) {
    let maxDist = 0;
    let j = 0;
    for (let i = 0; i < nums1.length; i++) {
        while (j < nums2.length && nums1[i] <= nums2[j]) {
            maxDist = Math.max(maxDist, j - i);
            j++;
        }
        if (j === nums2.length) break;
    }
    return maxDist;
};