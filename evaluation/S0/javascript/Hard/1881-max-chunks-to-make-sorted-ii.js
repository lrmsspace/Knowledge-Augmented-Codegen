// Source: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr.
//
// We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.
//
// Return the largest number of chunks we can make to sort the array.
//
// Example:
// Input: arr = [5,4,3,2,1]
// Output: 1
// Explanation:
// Splitting into two or more chunks will not return the required result.
// For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
//
// Constraints:
// 1 <= arr.length <= 2000
// 	0 <= arr[i] <= 108
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var maxChunksToSorted = function(arr) {
    

    let chunks = 0;
    let max = -Infinity;
    let min = Infinity;

    for (let i = 0; i < arr.length; i++) {
        max = Math.max(max, arr[i]);
        min = Math.min(min, arr[arr.length - 1 - i]);
        if (max <= min) {
            chunks++;
        }
    }
    return chunks;
    
};
