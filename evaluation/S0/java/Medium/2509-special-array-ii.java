// Source: https://leetcode.com/problems/special-array-ii/   |   Difficulty: Medium
//
// Problem Description:
// An array is considered special if every pair of its adjacent elements contains two numbers with different parity.
//
// You are given an array of integer nums and a 2D integer matrix queries, where for queries[i] = [fromi, toi] your task is to check that subarray nums[fromi..toi] is special or not.
//
// Return an array of booleans answer such that answer[i] is true if nums[fromi..toi] is special.
//
// Example:
// Input: nums = [3,4,1,2,6], queries = [[0,4]]
//
// Output: [false]
//
// Explanation:
//
// The subarray is [3,4,1,2,6]. 2 and 6 are both even.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= queries[i][0] <= queries[i][1] <= nums.length - 1
//

class Solution {
    public boolean[] isArraySpecial(int[] nums, int[][] queries) {
        int n = nums.length;
        boolean[] result = new boolean[queries.length];

        // Precompute an array to mark positions where adjacent elements have the same parity
        boolean[] sameParity = new boolean[n - 1];
        for (int i = 0; i < n - 1; i++) {
            sameParity[i] = (nums[i] % 2) == (nums[i + 1] % 2);
        }

        // Precompute a prefix sum array to quickly check for same parity in ranges
        int[] prefixSum = new int[n];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + (sameParity[i - 1] ? 1 : 0);
        }

        // Process each query
        for (int i = 0; i < queries.length; i++) {
            int from = queries[i][0];
            int to = queries[i][1];

            // Check if there are any same parity pairs in the range [from, to-1]
            if (prefixSum[to] - prefixSum[from] > 0) {
                result[i] = false;
            } else {
                result[i] = true;
            }
        }

        return result;          
    }
}
