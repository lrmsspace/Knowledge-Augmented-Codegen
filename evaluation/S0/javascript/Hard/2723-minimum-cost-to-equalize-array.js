// Source: https://leetcode.com/problems/minimum-cost-to-equalize-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers cost1 and cost2. You are allowed to perform either of the following operations any number of times:
//
//
// 	Choose an index i from nums and increase nums[i] by 1 for a cost of cost1.
// 	Choose two different indices i, j, from nums and increase nums[i] and nums[j] by 1 for a cost of cost2.
//
//
// Return the minimum cost required to make all elements in the array equal. 
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [4,1], cost1 = 5, cost2 = 2
//
// Output: 15
//
// Explanation: 
//
// The following operations can be performed to make the values equal:
//
//
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,2].
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,3].
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,4].
//
//
// The total cost is 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= cost1 <= 106
// 	1 <= cost2 <= 106
//

/**
 * @param {number[]} nums
 * @param {number} cost1
 * @param {number} cost2
 * @return {number}
 */
var minCostToEqualizeArray = function(nums, cost1, cost2) {
    const mod = 1e9 + 7;
    const n = nums.length;
    const maxNum = Math.max(...nums);
    let left = 0, right = maxNum;   
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        let cost = 0;
        for (let i = 0; i < n; i++) {
            if (nums[i] < mid) {
                cost += (mid - nums[i]) * cost1;
            } else if (nums[i] > mid) {
                cost += (nums[i] - mid) * cost1;
            }
        }
        if (cost <= cost2 * Math.floor(n / 2)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    let totalCost = 0;
    for (let i = 0; i < n; i++) {
        totalCost += Math.abs(nums[i] - left) * cost1;
    }
    return totalCost % mod; 
};
