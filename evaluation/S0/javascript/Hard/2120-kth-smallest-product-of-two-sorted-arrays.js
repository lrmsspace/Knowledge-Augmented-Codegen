// Source: https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/   |   Difficulty: Hard
//
// Problem Description:
// Given two sorted 0-indexed integer arrays nums1 and nums2 as well as an integer k, return the kth (1-based) smallest product of nums1[i] * nums2[j] where 0 <= i < nums1.length and 0 <= j < nums2.length.
//
// Example:
// Input: nums1 = [2,5], nums2 = [3,4], k = 2
// Output: 8
// Explanation: The 2 smallest products are:
// - nums1[0] * nums2[0] = 2 * 3 = 6
// - nums1[0] * nums2[1] = 2 * 4 = 8
// The 2nd smallest product is 8.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 5 * 104
// 	-105 <= nums1[i], nums2[j] <= 105
// 	1 <= k <= nums1.length * nums2.length
// 	nums1 and nums2 are sorted.
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number} k
 * @return {number}
 */
var kthSmallestProduct = function(nums1, nums2, k) {
    const countLessEqual = (x) => {
        let count = 0;
        let j = nums2.length - 1;
        for (let i = 0; i < nums1.length; i++) {
            while (j >= 0 && nums1[i] * nums2[j] > x) {
                j -= 1;
            }
            count += (j + 1);
        }
        return count;
    }
    let left = -1000000000;
    let right = 1000000000;
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (countLessEqual(mid) < k) {
            left = mid + 1;
        }
        else {            right = mid;
        }
    }
    return left;
};
