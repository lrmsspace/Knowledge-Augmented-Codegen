// Source: https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given two arrays of integers nums1 and nums2, return the number of triplets formed (type 1 and type 2) under the following rules:
//
//
// 	Type 1: Triplet (i, j, k) if nums1[i]2 == nums2[j] * nums2[k] where 0 <= i < nums1.length and 0 <= j < k < nums2.length.
// 	Type 2: Triplet (i, j, k) if nums2[i]2 == nums1[j] * nums1[k] where 0 <= i < nums2.length and 0 <= j < k < nums1.length.
//
// Example:
// Input: nums1 = [7,4], nums2 = [5,2,8,9]
// Output: 1
// Explanation: Type 1: (1, 1, 2), nums1[1]2 = nums2[1] * nums2[2]. (42 = 2 * 8).
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	1 <= nums1[i], nums2[i] <= 105
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var numTriplets = function(nums1, nums2) {
    const countMap = (arr) => {
        const map = new Map();
        const n = arr.length;
        for (let i = 0; i < n; i++) {
            for (let j = i + 1; j < n; j++) {
                const product = arr[i] * arr[j];
                map.set(product, (map.get(product) || 0) + 1);
            }
        }
        return map;
    };
    const map1 = countMap(nums1);
    const map2 = countMap(nums2);
    let tripletCount = 0;
    for (const num of nums1) {                  
        const square = num * num;
        if (map2.has(square)) {
            tripletCount += map2.get(square);
        }
    }
    for (const num of nums2) {
        const square = num * num;
        if (map1.has(square)) {
            tripletCount += map1.get(square);
        }
    }
    return tripletCount;    
};
