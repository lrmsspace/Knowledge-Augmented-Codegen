// Source: https://leetcode.com/problems/count-the-hidden-sequences/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of n integers differences, which describes the differences between each pair of consecutive integers of a hidden sequence of length (n + 1). More formally, call the hidden sequence hidden, then we have that differences[i] = hidden[i + 1] - hidden[i].
//
// You are further given two integers lower and upper that describe the inclusive range of values [lower, upper] that the hidden sequence can contain.
//
//
// 	For example, given differences = [1, -3, 4], lower = 1, upper = 6, the hidden sequence is a sequence of length 4 whose elements are in between 1 and 6 (inclusive).
//
// 	
// 		[3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences.
// 		[5, 6, 3, 7] is not possible since it contains an element greater than 6.
// 		[1, 2, 3, 4] is not possible since the differences are not correct.
// 	
// 	
//
//
// Return the number of possible hidden sequences there are. If there are no possible sequences, return 0.
//
// Example:
// Input: differences = [1,-3,4], lower = 1, upper = 6
// Output: 2
// Explanation: The possible hidden sequences are:
// - [3, 4, 1, 5]
// - [4, 5, 2, 6]
// Thus, we return 2.
//
// Constraints:
// n == differences.length
// 	1 <= n <= 105
// 	-105 <= differences[i] <= 105
// 	-105 <= lower <= upper <= 105
//

/**
 * @param {number[]} differences
 * @param {number} lower
 * @param {number} upper
 * @return {number}
 */
var numberOfArrays = function(differences, lower, upper) {
    let minPrefixSum = 0;
    let maxPrefixSum = 0;
    let currentPrefixSum = 0;
    for (const diff of differences) {
        currentPrefixSum += diff;
        minPrefixSum = Math.min(minPrefixSum, currentPrefixSum);
        maxPrefixSum = Math.max(maxPrefixSum, currentPrefixSum);
    }
    const range = upper - lower;
    const neededRange = maxPrefixSum - minPrefixSum;
    return neededRange <= range ? range - neededRange + 1 : 0;
};