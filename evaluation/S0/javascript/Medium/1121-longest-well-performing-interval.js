// Source: https://leetcode.com/problems/longest-well-performing-interval/   |   Difficulty: Medium
//
// Problem Description:
// We are given hours, a list of the number of hours worked per day for a given employee.
//
// A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
//
// A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
//
// Return the length of the longest well-performing interval.
//
// Example:
// Input: hours = [9,9,6,0,6,6,9]
// Output: 3
// Explanation: The longest well-performing interval is [9,9,6].
//
// Constraints:
// 1 <= hours.length <= 104
// 	0 <= hours[i] <= 16
//

/**
 * @param {number[]} hours
 * @return {number}
 */
var longestWPI = function(hours) {
    const n = hours.length;
    const prefixSum = new Array(n + 1).fill(0);
    const indexMap = new Map();
    let maxLength = 0;
    for (let i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + (hours[i] > 8 ? 1 : -1);
            


        if (prefixSum[i + 1] > 0) {
            maxLength = i + 1;
        } else {
            if (!indexMap.has(prefixSum[i + 1])) {
                indexMap.set(prefixSum[i + 1], i);
            }
            if (indexMap.has(prefixSum[i + 1] - 1)) {
                maxLength = Math.max(maxLength, i - indexMap.get(prefixSum[i + 1] - 1));
            }
        }
    }
    return maxLength;
    
};
