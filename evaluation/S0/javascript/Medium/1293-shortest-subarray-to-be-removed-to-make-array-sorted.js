// Source: https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.
//
// Return the length of the shortest subarray to remove.
//
// A subarray is a contiguous subsequence of the array.
//
// Example:
// Input: arr = [1,2,3,10,4,2,3,5]
// Output: 3
// Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
// Another correct solution is to remove the subarray [3,10,4].
//
// Constraints:
// 1 <= arr.length <= 105
// 	0 <= arr[i] <= 109
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var findLengthOfShortestSubarray = function(arr) {
    const n = arr.length;
    let right = n - 1;
    while (right > 0 && arr[right - 1] <= arr[right]) {
        right--;
    }
    if (right === 0) return 0;

    let result = right;
    let left = 0;
    while (left < n) {
        if (left > 0 && arr[left] < arr[left - 1]) break;
        while (right < n && arr[right] < arr[left]) {
            right++;
        }
        result = Math.min(result, right - left - 1);
        left++;
    }
    return result;
};