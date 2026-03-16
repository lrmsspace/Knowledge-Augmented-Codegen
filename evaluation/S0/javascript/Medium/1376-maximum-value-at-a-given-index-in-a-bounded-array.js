// Source: https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:
//
//
// 	nums.length == n
// 	nums[i] is a positive integer where 0 <= i < n.
// 	abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
// 	The sum of all the elements of nums does not exceed maxSum.
// 	nums[index] is maximized.
//
//
// Return nums[index] of the constructed array.
//
// Note that abs(x) equals x if x >= 0, and -x otherwise.
//
// Example:
// Input: n = 4, index = 2,  maxSum = 6
// Output: 2
// Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
// There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].
//
// Constraints:
// 1 <= n <= maxSum <= 109
// 	0 <= index < n
//

/**
 * @param {number} n
 * @param {number} index
 * @param {number} maxSum
 * @return {number}
 */
var maxValue = function(n, index, maxSum) {
    const canConstruct = (value) => {
        const leftLength = index;
        const rightLength = n - index - 1;
        const leftSum = leftLength >= value - 1
            ? ((value - 1 + value - leftLength) * leftLength) / 2
            : ((value - 1 + 1) * (value - 1)) / 2 + (leftLength - (value - 1));
        const rightSum = rightLength >= value - 1
            ? ((value - 1 + value - rightLength) * rightLength) / 2
            : ((value - 1 + 1) * (value - 1)) / 2 + (rightLength - (value - 1));
        const totalSum = leftSum + rightSum + value;
        return totalSum <= maxSum;
    };

    let left = 1;
    let right = maxSum;
    let result = 1;
    while (left <= right) {                     
        const mid = Math.floor((left + right) / 2);
        if (canConstruct(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
};  