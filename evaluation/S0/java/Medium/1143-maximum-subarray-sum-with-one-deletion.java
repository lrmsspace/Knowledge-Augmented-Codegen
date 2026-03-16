// Source: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.
//
// Note that the subarray needs to be non-empty after deleting one element.
//
// Example:
// Input: arr = [1,-2,0,3]
// Output: 4
// Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
//
// Constraints:
// 1 <= arr.length <= 105
// 	-104 <= arr[i] <= 104
//

class Solution {
    public int maximumSum(int[] arr) {
        int n = arr.length;
        int[] forward = new int[n];
        int[] backward = new int[n];

        forward[0] = arr[0];
        int maxSum = arr[0];

        // Forward pass to calculate maximum subarray sum ending at each index
        for (int i = 1; i < n; i++) {
            forward[i] = Math.max(arr[i], forward[i - 1] + arr[i]);
            maxSum = Math.max(maxSum, forward[i]);
        }

        backward[n - 1] = arr[n - 1];

        // Backward pass to calculate maximum subarray sum starting at each index
        for (int i = n - 2; i >= 0; i--) {
            backward[i] = Math.max(arr[i], backward[i + 1] + arr[i]);
        }

        // Calculate maximum sum with one deletion
        for (int i = 1; i < n - 1; i++) {
            maxSum = Math.max(maxSum, forward[i - 1] + backward[i + 1]);
        }

        return maxSum;          
    }
}
