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

class Solution {
    public int minCostToEqualizeArray(int[] nums, int cost1, int cost2) {
        long mod = 1_000_000_007;
        long totalCost = 0;
        int maxNum = Integer.MIN_VALUE;

        for (int num : nums) {
            maxNum = Math.max(maxNum, num);
        }

        for (int num : nums) {
            int diff = maxNum - num;
            if (2 * cost1 <= cost2) {
                totalCost += (long) diff * cost1;
            } else {
                totalCost += (long) (diff / 2) * cost2 + (diff % 2) * cost1;
            }
            totalCost %= mod;
        }

        return (int) totalCost;         
    }
}
