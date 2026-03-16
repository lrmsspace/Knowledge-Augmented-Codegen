// Source: https://leetcode.com/problems/k-concatenation-maximum-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr and an integer k, modify the array by repeating it k times.
//
// For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].
//
// Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.
//
// As the answer can be very large, return the answer modulo 109 + 7.
//
// Example:
// Input: arr = [1,2], k = 3
// Output: 9
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= k <= 105
// 	-104 <= arr[i] <= 104
//

int kConcatenationMaxSum(int* arr, int arrSize, int k) {
    long long MOD = 1000000007;
    long long max_ending_here = 0;
    long long max_so_far = 0;
    long long total_sum = 0;

    for (int i = 0; i < arrSize; i++) {
        total_sum += arr[i];
        max_ending_here = (max_ending_here + arr[i] > 0) ? max_ending_here + arr[i] : 0;
        max_so_far = (max_so_far > max_ending_here) ? max_so_far : max_ending_here;
    }

    if (k == 1) {
        return max_so_far % MOD;
    }

    long long max_prefix_sum = 0;
    long long current_prefix_sum = 0;
    for (int i = 0; i < arrSize; i++) {
        current_prefix_sum += arr[i];
        max_prefix_sum = (max_prefix_sum > current_prefix_sum) ? max_prefix_sum : current_prefix_sum;
    }

    long long max_suffix_sum = 0;
    long long current_suffix_sum = 0;
    for (int i = arrSize - 1; i >= 0; i--) {
        current_suffix_sum += arr[i];
        max_suffix_sum = (max_suffix_sum > current_suffix_sum) ? max_suffix_sum : current_suffix_sum;
    }

    if (total_sum > 0) {
        return (max_prefix_sum + max_suffix_sum + (k - 2) * total_sum) % MOD;
    } else {
        return (max_prefix_sum + max_suffix_sum) % MOD;
    }       
}
