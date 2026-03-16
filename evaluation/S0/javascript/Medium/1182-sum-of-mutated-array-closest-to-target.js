// Source: https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.
//
// In case of a tie, return the minimum such integer.
//
// Notice that the answer is not neccesarilly a number from arr.
//
// Example:
// Input: arr = [4,9,3], target = 10
// Output: 3
// Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
//
// Constraints:
// 1 <= arr.length <= 104
// 	1 <= arr[i], target <= 105
//

/**
 * @param {number[]} arr
 * @param {number} target
 * @return {number}
 */
var findBestValue = function(arr, target) {
    arr.sort((a, b) => a - b);
    const n = arr.length;
    let prefixSum = new Array(n + 1).fill(0);
    for (let i = 1; i <= n; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i - 1];
    }
    let left = 0, right = arr[n - 1];
    let bestValue = -1;
    while (left <= right) {
        let mid = Math.floor((left + right) / 2);
        let idx = lowerBound(arr, mid);
        let currentSum = prefixSum[idx] + (n - idx) * mid;
        if (currentSum < target) {
            bestValue = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    const sumWithBest = calculateSum(arr, bestValue);
    const sumWithNext = calculateSum(arr, bestValue + 1);
    if (Math.abs(sumWithNext - target) < Math.abs(sumWithBest - target)) {
        return bestValue + 1;
    }
    return bestValue;   
            
};
