// Source: https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and two integers k and threshold, return the number of sub-arrays of size k and average greater than or equal to threshold.
//
// Example:
// Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
// Output: 3
// Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively. All other sub-arrays of size 3 have averages less than 4 (the threshold).
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 104
// 	1 <= k <= arr.length
// 	0 <= threshold <= 104
//

int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
    int count = 0;
    int required_sum = threshold * k;
    int current_sum = 0;

    // Calculate the sum of the first 'k' elements
    for (int i = 0; i < k; i++) {
        current_sum += arr[i];
    }

    // Check if the first window meets the condition
    if (current_sum >= required_sum) {
        count++;
    }

    // Slide the window across the array
    for (int i = k; i < arrSize; i++) {
        current_sum += arr[i] - arr[i - k]; // Add new element and remove the oldest element

        if (current_sum >= required_sum) {
            count++;
        }
    }

    return count;       
}
