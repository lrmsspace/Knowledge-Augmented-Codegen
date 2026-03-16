// Source: https://leetcode.com/problems/beautiful-towers-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array maxHeights of n integers.
//
// You are tasked with building n towers in the coordinate line. The ith tower is built at coordinate i and has a height of heights[i].
//
// A configuration of towers is beautiful if the following conditions hold:
//
//
// 	1 <= heights[i] <= maxHeights[i]
// 	heights is a mountain array.
//
//
// Array heights is a mountain if there exists an index i such that:
//
//
// 	For all 0 < j <= i, heights[j - 1] <= heights[j]
// 	For all i <= k < n - 1, heights[k + 1] <= heights[k]
//
//
// Return the maximum possible sum of heights of a beautiful configuration of towers.
//
// Example:
// Input: maxHeights = [5,3,4,1,1]
// Output: 13
// Explanation: One beautiful configuration with a maximum sum is heights = [5,3,3,1,1]. This configuration is beautiful since:
// - 1 <= heights[i] <= maxHeights[i]  
// - heights is a mountain of peak i = 0.
// It can be shown that there exists no other beautiful configuration with a sum of heights greater than 13.
//
// Constraints:
// 1 <= n == maxHeights.length <= 105
// 	1 <= maxHeights[i] <= 109
//

/**
 * @param {number[]} maxHeights
 * @return {number}
 */
var maximumSumOfHeights = function(maxHeights) {
    const n = maxHeights.length;
    const leftDP = Array(n).fill(0);
    const rightDP = Array(n).fill(0);
    for (let i = 0; i < n; i++) {
        leftDP[i] = maxHeights[i];  
        if (i > 0) {
            leftDP[i] += Math.min(leftDP[i - 1], maxHeights[i]);
        }
    }
    for (let i = n - 1; i >= 0; i--) {
        rightDP[i] = maxHeights[i];
        if (i < n - 1) {
            rightDP[i] += Math.min(rightDP[i + 1], maxHeights[i]);
        }
    }
    let maxSum = 0;
    for (let i = 0; i < n; i++) {
        maxSum = Math.max(maxSum, leftDP[i] + rightDP[i] - maxHeights[i]);
    }
    return maxSum;  
};
