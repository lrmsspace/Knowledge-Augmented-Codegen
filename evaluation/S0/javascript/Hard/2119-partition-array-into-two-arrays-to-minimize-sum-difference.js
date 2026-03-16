// Source: https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
//
// Return the minimum possible absolute difference.
//
// Example:
// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
//
// Constraints:
// 1 <= n <= 15
// 	nums.length == 2 * n
// 	-107 <= nums[i] <= 107
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumDifference = function(nums) {
    const n = nums.length / 2;
    const leftSums = new Map();
    const rightSums = new Map();
    const generateSums = (arr, sumsMap) => {
        const m = arr.length;
        for (let mask = 0; mask < (1 << m); mask++) {
            let sum = 0;
            for (let i = 0; i < m; i++) {
                if (mask & (1 << i)) {
                    sum += arr[i];
                }
            }
            const count = sumsMap.get(sum) || 0;
            sumsMap.set(sum, count + 1);
        }
    };

    generateSums(nums.slice(0, n), leftSums);
    generateSums(nums.slice(n), rightSums);
    const totalSum = nums.reduce((a, b) => a + b, 0);
    let minDiff = Infinity;
    for (const [leftSum, count] of leftSums.entries()) {
        const target = totalSum / 2 - leftSum;
        let closestRightSum = null;
        for (const rightSum of rightSums.keys()) {  
            if (closestRightSum === null || Math.abs(rightSum - target) < Math.abs(closestRightSum - target)) {
                closestRightSum = rightSum;
            }
        }
        const currentDiff = Math.abs((leftSum + closestRightSum) - (totalSum - leftSum - closestRightSum));
        minDiff = Math.min(minDiff, currentDiff);
    }
    return minDiff; 
};
