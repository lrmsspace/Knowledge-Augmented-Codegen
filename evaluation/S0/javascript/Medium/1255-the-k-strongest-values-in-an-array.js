// Source: https://leetcode.com/problems/the-k-strongest-values-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and an integer k.
//
// A value arr[i] is said to be stronger than a value arr[j] if |arr[i] - m| > |arr[j] - m| where m is the centre of the array.
// If |arr[i] - m| == |arr[j] - m|, then arr[i] is said to be stronger than arr[j] if arr[i] > arr[j].
//
// Return a list of the strongest k values in the array. return the answer in any arbitrary order.
//
// The centre is the middle value in an ordered integer list. More formally, if the length of the list is n, the centre is the element in position ((n - 1) / 2) in the sorted list (0-indexed).
//
//
// 	For arr = [6, -3, 7, 2, 11], n = 5 and the centre is obtained by sorting the array arr = [-3, 2, 6, 7, 11] and the centre is arr[m] where m = ((5 - 1) / 2) = 2. The centre is 6.
// 	For arr = [-7, 22, 17, 3], n = 4 and the centre is obtained by sorting the array arr = [-7, 3, 17, 22] and the centre is arr[m] where m = ((4 - 1) / 2) = 1. The centre is 3.
//
// Example:
// Input: arr = [1,2,3,4,5], k = 2
// Output: [5,1]
// Explanation: Centre is 3, the elements of the array sorted by the strongest are [5,1,4,2,3]. The strongest 2 elements are [5, 1]. [1, 5] is also accepted answer.
// Please note that although |5 - 3| == |1 - 3| but 5 is stronger than 1 because 5 > 1.
//
// Constraints:
// 1 <= arr.length <= 105
// 	-105 <= arr[i] <= 105
// 	1 <= k <= arr.length
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number[]}
 */
var getStrongest = function(arr, k) {
    arr.sort((a, b) => a - b);
    const n = arr.length;
    const m = arr[Math.floor((n - 1) / 2)];
    arr.sort((a, b) => {
        const diffA = Math.abs(a - m);
        const diffB = Math.abs(b - m);
        if (diffA === diffB) {
            return b - a;
        }
        return diffB - diffA;
    }
    );
    return arr.slice(0, k); 
                
};
