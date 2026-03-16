// Source: https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of integers nums of length n.
//
// The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.
//
// You need to divide nums into 3 disjoint contiguous subarrays.
//
// Return the minimum possible sum of the cost of these subarrays.
//
// Example:
// Input: nums = [1,2,3,12]
// Output: 6
// Explanation: The best possible way to form 3 subarrays is: [1], [2], and [3,12] at a total cost of 1 + 2 + 3 = 6.
// The other possible ways to form 3 subarrays are:
// - [1], [2,3], and [12] at a total cost of 1 + 2 + 12 = 15.
// - [1,2], [3], and [12] at a total cost of 1 + 3 + 12 = 16.
//
// Constraints:
// 3 <= n <= 50
// 	1 <= nums[i] <= 50
//

class Solution {
    public int minimumCost(int[] nums) {
        int n = nums.length;
        int minCost = Integer.MAX_VALUE;

        // Iterate through all possible first and second subarray starting points
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int cost = nums[0] + nums[i] + nums[j];
                minCost = Math.min(minCost, cost);
            }
        }

        return minCost;         
    }
}
