// Source: https://leetcode.com/problems/choose-k-elements-with-maximum-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, nums1 and nums2, both of length n, along with a positive integer k.
//
// For each index i from 0 to n - 1, perform the following:
//
//
// 	Find all indices j where nums1[j] is less than nums1[i].
// 	Choose at most k values of nums2[j] at these indices to maximize the total sum.
//
//
// Return an array answer of size n, where answer[i] represents the result for the corresponding index i.
//
// Example:
// Input: nums1 = [4,2,1,5,3], nums2 = [10,20,30,40,50], k = 2
//
// Output: [80,30,0,80,50]
//
// Explanation:
//
//
// 	For i = 0: Select the 2 largest values from nums2 at indices [1, 2, 4] where nums1[j] < nums1[0], resulting in 50 + 30 = 80.
// 	For i = 1: Select the 2 largest values from nums2 at index [2] where nums1[j] < nums1[1], resulting in 30.
// 	For i = 2: No indices satisfy nums1[j] < nums1[2], resulting in 0.
// 	For i = 3: Select the 2 largest values from nums2 at indices [0, 1, 2, 4] where nums1[j] < nums1[3], resulting in 50 + 30 = 80.
// 	For i = 4: Select the 2 largest values from nums2 at indices [1, 2] where nums1[j] < nums1[4], resulting in 30 + 20 = 50.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 106
// 	1 <= k <= n
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number} k
 * @return {number[]}
 */
var findMaxSum = function(nums1, nums2, k) {
    const n = nums1.length;
    const pairs = [];
    for (let i = 0; i < n; i++) {
        pairs.push([nums1[i], nums2[i]]);
    }
    pairs.sort((a, b) => a[0] - b[0]);
    const result = new Array(n).fill(0);
    const maxHeap = [];
    let sum = 0;
    for (let i = 0; i < n; i++) {
        while (maxHeap.length > 0 && maxHeap[0][0] < pairs[i][0]) {
            const [value, index] = maxHeap.shift();
            sum += value;
            if (maxHeap.length > k) {
                sum -= maxHeap.pop()[0];
            }
        }
        result[i] = sum;
        maxHeap.push(pairs[i]);
        maxHeap.sort((a, b) => b[0] - a[0]);
    }
    return result;
};
