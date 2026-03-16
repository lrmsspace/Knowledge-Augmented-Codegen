// Source: https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
//
// Example:
// Input: arr = [5,5,4], k = 1
// Output: 1
// Explanation: Remove the single 4, only 5 is left.
//
// Constraints:
// 1 <= arr.length <= 10^5
// 	1 <= arr[i] <= 10^9
// 	0 <= k <= arr.length
//

/**

 * @param {number[]} arr

 * @param {number} k

 * @return {number}

 */

var findLeastNumOfUniqueInts = function(arr, k) {

    

    const frequencyMap = new Map();
    for (const num of arr) {
        frequencyMap.set(num, (frequencyMap.get(num) || 0) + 1);
    }

    const frequencies = Array.from(frequencyMap.values());
    frequencies.sort((a, b) => a - b);

    let uniqueCount = frequencies.length;
    for (const freq of frequencies) {
        if (k >= freq) {
            k -= freq;
            uniqueCount--;
        } else {
            break;
        }
    }
    return uniqueCount;
    
};
