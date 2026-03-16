// Source: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr, return the number of subarrays with an odd sum.
//
// Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: arr = [1,3,5]
// Output: 4
// Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
// All sub-arrays sum are [1,4,9,3,8,5].
// Odd sums are [1,9,3,5] so the answer is 4.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 100
//

int numOfSubarrays(int* arr, int arrSize) {
    const int MOD = 1e9 + 7;
    long long odd_count = 0;
    long long even_count = 1; // empty subarray
    long long total_odd_subarrays = 0;
    long long prefix_sum = 0;

    for (int i = 0; i < arrSize; i++) {
        prefix_sum += arr[i];

        if (prefix_sum % 2 == 0) {
            total_odd_subarrays = (total_odd_subarrays + odd_count) % MOD;
            even_count++;
        } else {
            total_odd_subarrays = (total_odd_subarrays + even_count) % MOD;
            odd_count++;
        }
    }

    return (int)(total_odd_subarrays % MOD);        
}
