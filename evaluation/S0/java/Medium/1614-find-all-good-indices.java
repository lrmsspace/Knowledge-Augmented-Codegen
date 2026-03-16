// Source: https://leetcode.com/problems/find-all-good-indices/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of size n and a positive integer k.
//
// We call an index i in the range k <= i < n - k good if the following conditions are satisfied:
//
//
// 	The k elements that are just before the index i are in non-increasing order.
// 	The k elements that are just after the index i are in non-decreasing order.
//
//
// Return an array of all good indices sorted in increasing order.
//
// Example:
// Input: nums = [2,1,1,1,3,4,1], k = 2
// Output: [2,3]
// Explanation: There are two good indices in the array:
// - Index 2. The subarray [2,1] is in non-increasing order, and the subarray [1,3] is in non-decreasing order.
// - Index 3. The subarray [1,1] is in non-increasing order, and the subarray [3,4] is in non-decreasing order.
// Note that the index 4 is not good because [4,1] is not non-decreasing.
//
// Constraints:
// n == nums.length
// 	3 <= n <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= n / 2
//

class Solution {
    public List<Integer> goodIndices(int[] nums, int k) {
        int n = nums.length;
        int[] nonInc = new int[n];
        int[] nonDec = new int[n];

        // Fill nonInc array
        for (int i = 1; i < n; i++) {
            if (nums[i] <= nums[i - 1]) {
                nonInc[i] = nonInc[i - 1] + 1;
            } else {
                nonInc[i] = 0;
            }
        }

        // Fill nonDec array
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] <= nums[i + 1]) {
                nonDec[i] = nonDec[i + 1] + 1;
            } else {
                nonDec[i] = 0;
            }
        }

        List<Integer> result = new ArrayList<>();
        for (int i = k; i < n - k; i++) {
            if (nonInc[i - 1] >= k && nonDec[i + 1] >= k) {
                result.add(i);
            }
        }

        return result;          
    }
}
