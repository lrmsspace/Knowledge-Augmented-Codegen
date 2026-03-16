// Source: https://leetcode.com/problems/advantage-shuffle/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 both of the same length. The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].
//
// Return any permutation of nums1 that maximizes its advantage with respect to nums2.
//
// Example:
// Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
// Output: [2,11,7,15]
//
// Constraints:
// 1 <= nums1.length <= 105
// 	nums2.length == nums1.length
// 	0 <= nums1[i], nums2[i] <= 109
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number[]}
 */
var advantageCount = function(nums1, nums2) {
    const n = nums1.length;
    const sortedNums1 = [...nums1].sort((a, b) => a - b);
    const indexedNums2 = nums2.map((value, index) => ({ value, index }))
                               .sort((a, b) => a.value - b.value);  
    const result = Array(n);
    let left = 0;
    let right = n - 1;
    for (let i = 0; i < n; i++) {
        const { value: num2Value, index: num2Index } = indexedNums2[i];
        if (sortedNums1[right] > num2Value) {
            result[num2Index] = sortedNums1[right];
            right--;
        } else {
            result[num2Index] = sortedNums1[left];
            left++;
        }
    }
    return result;
};  