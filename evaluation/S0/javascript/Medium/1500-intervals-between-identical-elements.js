// Source: https://leetcode.com/problems/intervals-between-identical-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of n integers arr.
//
// The interval between two elements in arr is defined as the absolute difference between their indices. More formally, the interval between arr[i] and arr[j] is |i - j|.
//
// Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] and each element in arr with the same value as arr[i].
//
// Note: |x| is the absolute value of x.
//
// Example:
// Input: arr = [2,1,3,1,2,3,3]
// Output: [4,2,7,2,4,4,5]
// Explanation:
// - Index 0: Another 2 is found at index 4. |0 - 4| = 4
// - Index 1: Another 1 is found at index 3. |1 - 3| = 2
// - Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
// - Index 3: Another 1 is found at index 1. |3 - 1| = 2
// - Index 4: Another 2 is found at index 0. |4 - 0| = 4
// - Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
// - Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5
//
// Constraints:
// n == arr.length
// 	1 <= n <= 105
// 	1 <= arr[i] <= 105
//
//
//  
// Note: This question is the same as  2615: Sum of Distances.
//

/**
 * @param {number[]} arr
 * @return {number[]}
 */
var getDistances = function(arr) {
    const n = arr.length;
    const result = new Array(n).fill(0);
    const indexMap = new Map();
    for (let i = 0; i < n; i++) {
        if (!indexMap.has(arr[i])) {
            indexMap.set(arr[i], []);
        }
        indexMap.get(arr[i]).push(i);
    }
    for (const indices of indexMap.values()) {
        const m = indices.length;
        const prefixSums = new Array(m).fill(0);
        for (let i = 1; i < m; i++) {
            prefixSums[i] = prefixSums[i - 1] + indices[i - 1];
        }
        for (let i = 0; i < m; i++) {
            const index = indices[i];
            const leftCount = i;
            const rightCount = m - i - 1;
            const leftSum = prefixSums[i];
            const rightSum = prefixSums[m - 1] - prefixSums[i];
            result[index] = (index * leftCount - leftSum) + (rightSum - index * rightCount);
        }
    }
    return result;  
};
