// Source: https://leetcode.com/problems/minimum-cost-to-make-array-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums and cost consisting each of n positive integers.
//
// You can do the following operation any number of times:
//
//
// 	Increase or decrease any element of the array nums by 1.
//
//
// The cost of doing one operation on the ith element is cost[i].
//
// Return the minimum total cost such that all the elements of the array nums become equal.
//
// Example:
// Input: nums = [1,3,5,2], cost = [2,3,1,14]
// Output: 8
// Explanation: We can make all the elements equal to 2 in the following way:
// - Increase the 0th element one time. The cost is 2.
// - Decrease the 1st element one time. The cost is 3.
// - Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
// The total cost is 2 + 3 + 3 = 8.
// It can be shown that we cannot make the array equal with a smaller cost.
//
// Constraints:
// n == nums.length == cost.length
// 	1 <= n <= 105
// 	1 <= nums[i], cost[i] <= 106
// 	Test cases are generated in a way that the output doesn't exceed 253-1
//

/**
 * @param {number[]} nums
 * @param {number[]} cost
 * @return {number}
 */
var minCost = function(nums, cost) {
    const n = nums.length;
    const pairs = [];
    for (let i = 0; i < n; i++) {
        pairs.push([nums[i], cost[i]]);
    }
    pairs.sort((a, b) => a[0] - b[0]);

    let totalCost = 0;
    for (const [_, c] of pairs) {
        totalCost += c;
    }
    let accumulatedCost = 0;
    for (const [num, c] of pairs) {
        accumulatedCost += c;
        if (accumulatedCost >= totalCost / 2) {
            return pairs.reduce((cost, [n, c]) => cost + Math.abs(n - num) * c, 0);
        }
    }
    return 0;

};
