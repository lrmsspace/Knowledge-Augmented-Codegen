// Source: https://leetcode.com/problems/kth-missing-positive-number/   |   Difficulty: Easy
//
// Problem Description:
// Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
//
// Return the kth positive integer that is missing from this array.
//
// Example:
// Input: arr = [2,3,4,7,11], k = 5
// Output: 9
// Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.
//
// Constraints:
// 1 <= arr.length <= 1000
// 	1 <= arr[i] <= 1000
// 	1 <= k <= 1000
// 	arr[i] < arr[j] for 1 <= i < j <= arr.length
//
//
//  
// Follow up:
//
// Could you solve this problem in less than O(n) complexity?
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
var findKthPositive = function(arr, k) {
    let missingCount = 0;
    let currentNumber = 1;
    let arrIndex = 0;
    while (missingCount < k) {
        if (arrIndex < arr.length && arr[arrIndex] === currentNumber) {
            arrIndex++;
        } else {
            missingCount++;
        }
        if (missingCount === k) {
            return currentNumber;
        }
        currentNumber++;
    }
    return -1; // This line should never be reached 
};