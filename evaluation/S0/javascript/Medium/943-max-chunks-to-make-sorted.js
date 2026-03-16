// Source: https://leetcode.com/problems/max-chunks-to-make-sorted/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array arr of length n that represents a permutation of the integers in the range [0, n - 1].
//
// We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.
//
// Return the largest number of chunks we can make to sort the array.
//
// Example:
// Input: arr = [4,3,2,1,0]
// Output: 1
// Explanation:
// Splitting into two or more chunks will not return the required result.
// For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
//
// Constraints:
// n == arr.length
// 	1 <= n <= 10
// 	0 <= arr[i] < n
// 	All the elements of arr are unique.
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var maxChunksToSorted = function(arr) {
    let chunks = 0;
    let maxSoFar = -1;
    for (let i = 0; i < arr.length; i++) {
        maxSoFar = Math.max(maxSoFar, arr[i]);
        if (maxSoFar === i) {
            chunks++;
        }
    }
    return chunks;
};