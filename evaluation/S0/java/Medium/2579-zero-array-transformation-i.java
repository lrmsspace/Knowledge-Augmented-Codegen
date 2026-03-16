// Source: https://leetcode.com/problems/zero-array-transformation-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri].
//
// For each queries[i]:
//
//
// 	Select a subset of indices within the range [li, ri] in nums.
// 	Decrement the values at the selected indices by 1.
//
//
// A Zero Array is an array where all elements are equal to 0.
//
// Return true if it is possible to transform nums into a Zero Array after processing all the queries sequentially, otherwise return false.
//
// Example:
// Input: nums = [1,0,1], queries = [[0,2]]
//
// Output: true
//
// Explanation:
//
//
// 	For i = 0:
//
// 	
// 		Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
// 		The array will become [0, 0, 0], which is a Zero Array.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= li <= ri < nums.length
//

class Solution {
    public boolean isZeroArray(int[] nums, int[][] queries) {
        int n = nums.length;
        int[] diff = new int[n + 1];

        // Build the difference array based on the queries
        for (int[] query : queries) {
            int l = query[0];
            int r = query[1];
            diff[l] += 1;
            if (r + 1 < n) {
                diff[r + 1] -= 1;
            }
        }

        // Calculate the prefix sum to get the number of decrements for each index
        for (int i = 1; i < n; i++) {
            diff[i] += diff[i - 1];
        }

        // Check if each element in nums can be reduced to zero
        for (int i = 0; i < n; i++) {
            if (nums[i] < diff[i]) {
                return false;
            }
        }

        return true;            
    }
}
