// Source: https://leetcode.com/problems/make-k-subarray-sums-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr and an integer k. The array arr is circular. In other words, the first element of the array is the next element of the last element, and the last element of the array is the previous element of the first element.
//
// You can do the following operation any number of times:
//
//
// 	Pick any element from arr and increase or decrease it by 1.
//
//
// Return the minimum number of operations such that the sum of each subarray of length k is equal.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: arr = [1,4,1,3], k = 2
// Output: 1
// Explanation: we can do one operation on index 1 to make its value equal to 3.
// The array after the operation is [1,3,1,3]
// - Subarray starts at index 0 is [1, 3], and its sum is 4 
// - Subarray starts at index 1 is [3, 1], and its sum is 4 
// - Subarray starts at index 2 is [1, 3], and its sum is 4 
// - Subarray starts at index 3 is [3, 1], and its sum is 4
//
// Constraints:
// 1 <= k <= arr.length <= 105
// 	1 <= arr[i] <= 109
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
var makeSubKSumEqual = function(arr, k) {
    const n = arr.length;
    const visited = new Array(n).fill(false);
    let totalOperations = 0;
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            const indices = [];
            let current = i;
            while (!visited[current]) {
                visited[current] = true;
                indices.push(current);
                current = (current + k) % n;
            }
            const values = indices.map(index => arr[index]);
            values.sort((a, b) => a - b);
            const median = values[Math.floor(values.length / 2)];
            for (const value of values) {
                totalOperations += Math.abs(value - median);
            }
        }
    }
    return totalOperations;
        
};
