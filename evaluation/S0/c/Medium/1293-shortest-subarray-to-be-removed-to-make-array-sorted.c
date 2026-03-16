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

int findLengthOfShortestSubarray(int* arr, int arrSize) {
    int left = 0, right = arrSize - 1;

    // Find the longest non-decreasing prefix
    while (left + 1 < arrSize && arr[left] <= arr[left + 1]) {
        left++;
    }

    // If the entire array is non-decreasing
    if (left == arrSize - 1) {
        return 0;
    }

    // Find the longest non-decreasing suffix
    while (right - 1 >= 0 && arr[right - 1] <= arr[right]) {
        right--;
    }

    // Initialize the result with removing either the prefix or suffix
    int result = fmin(arrSize - left - 1, right);

    // Try to merge prefix and suffix
    for (int i = 0; i <= left; i++) {
        // Binary search for the smallest index in the suffix where arr[j] >= arr[i]
        int low = right, high = arrSize;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= arr[i]) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        // Calculate the length of the subarray to remove
        result = fmin(result, low - i - 1);
    }

    return result;      
}
