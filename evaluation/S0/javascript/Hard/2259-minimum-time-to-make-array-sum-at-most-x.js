// Source: https://leetcode.com/problems/minimum-time-to-make-array-sum-at-most-x/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of equal length. Every second, for all indices 0 <= i < nums1.length, value of nums1[i] is incremented by nums2[i]. After this is done, you can do the following operation:
//
//
//  Choose an index 0 <= i < nums1.length and make nums1[i] = 0.
//
//
// You are also given an integer x.
//
// Return the minimum time in which you can make the sum of all elements of nums1 to be less than or equal to x, or -1 if this is not possible.
//
// Example:
// Input: nums1 = [1,2,3], nums2 = [1,2,3], x = 4
// Output: 3
// Explanation: 
// For the 1st second, we apply the operation on i = 0. Therefore nums1 = [0,2+2,3+3] = [0,4,6]. 
// For the 2nd second, we apply the operation on i = 1. Therefore nums1 = [0+1,0,6+3] = [1,0,9]. 
// For the 3rd second, we apply the operation on i = 2. Therefore nums1 = [1+1,0+2,0] = [2,2,0]. 
// Now sum of nums1 = 4. It can be shown that these operations are optimal, so we return 3.
//
// Constraints:
// 1 <= nums1.length <= 103
//  1 <= nums1[i] <= 103
//  0 <= nums2[i] <= 103
//  nums1.length == nums2.length
//  0 <= x <= 106
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number} x
 * @return {number}
 */
var minimumTime = function(nums1, nums2, x) {
    const n = nums1.length;
    let left = 0;
    let right = 1000000;
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        let sum = 0;
        for (let i = 0; i < n; i++) {
            sum += Math.max(0, nums1[i] + nums2[i] * mid - mid);
        }
        if (sum <= x) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return left === 1000000 ? -1 : left;
};
