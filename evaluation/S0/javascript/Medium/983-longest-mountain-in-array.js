// Source: https://leetcode.com/problems/longest-mountain-in-array/   |   Difficulty: Medium
//
// Problem Description:
// You may recall that an array arr is a mountain array if and only if:
//
//
// 	arr.length >= 3
// 	There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
// 	
// 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
// 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
// 	
// 	
//
//
// Given an integer array arr, return the length of the longest subarray, which is a mountain. Return 0 if there is no mountain subarray.
//
// Example:
// Input: arr = [2,1,4,7,3,2,5]
// Output: 5
// Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 104
//
//
//  
// Follow up:
//
//
// 	Can you solve it using only one pass?
// 	Can you solve it in O(1) space?
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var longestMountain = function(arr) {
    const n = arr.length;
    let maxLength = 0;
    let i = 1;
    while (i < n - 1) {
        // Find the start of a potential mountain
        while (i < n - 1 && (arr[i] <= arr[i - 1] || arr[i] <= arr[i + 1])) {
            i++;
        }
        let left = i - 1;
        let right = i + 1;
        // Expand left while strictly increasing
        while (left > 0 && arr[left] > arr[left - 1]) {
            left--;
        }
        // Expand right while strictly decreasing
        while (right < n - 1 && arr[right] > arr[right + 1]) {
            right++;
        }
        if (left < i && right > i) {
            maxLength = Math.max(maxLength, right - left + 1);
        }
        i = right + 1;
    }
    return maxLength;
};