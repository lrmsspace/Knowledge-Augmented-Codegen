// Source: https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.
//
// Return the length of the shortest subarray to remove.
//
// A subarray is a contiguous subsequence of the array.
//
// Example:
// Input: arr = [1,2,3,10,4,2,3,5]
// Output: 3
// Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
// Another correct solution is to remove the subarray [3,10,4].
//
// Constraints:
// 1 <= arr.length <= 105
// 	0 <= arr[i] <= 109
//

class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int right = n - 1;

        // Find the longest non-decreasing suffix
        while (right > 0 && arr[right - 1] <=  arr[right]) {
            right--;
        }

        // If the whole array is non-decreasing
        if (right == 0) {
            return 0;
        }

        int minLength = right; // Remove prefix

        // Try to merge prefix and suffix
        for (int left = 0; left < n; ++left) {
            if (left > 0 && arr[left] < arr[left - 1]) {
                break; // Prefix is no longer non-decreasing
            }

            // Move right pointer to find a valid merge point
            while (right < n && arr[right] < arr[left]) {
                right++;
            }

            // Calculate the length of the subarray to remove
            minLength = min(minLength, right - left - 1);
        }

        return minLength;           
    }
};
