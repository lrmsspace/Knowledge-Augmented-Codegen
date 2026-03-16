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

class Solution {
    public long minCost(int[] nums, int[] cost) {
        int n = nums.length;
        long left = 1, right = (long)1e6;
        long result = Long.MAX_VALUE;

        while (left <= right) {
            long mid = left + (right - left) / 2;
            long costMid = calculateCost(nums, cost, mid);
            long costMidPlusOne = calculateCost(nums, cost, mid + 1);

            result = Math.min(result, costMid);

            if (costMid < costMidPlusOne) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return result;          
    }
}
