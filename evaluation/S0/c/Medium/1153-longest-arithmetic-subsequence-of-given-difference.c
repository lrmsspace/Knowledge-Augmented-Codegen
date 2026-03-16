// Source: https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.
//
// A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: arr = [1,2,3,4], difference = 1
// Output: 4
// Explanation: The longest arithmetic subsequence is [1,2,3,4].
//
// Constraints:
// 1 <= arr.length <= 105
// 	-104 <= arr[i], difference <= 104
//

int longestSubsequence(int* arr, int arrSize, int difference) {
    int maxLength = 0;
    int hashSize = 20001; // To accommodate values from -10^4 to 10^4
    int* dp = (int*)calloc(hashSize, sizeof(int));

    for (int i = 0; i < arrSize; i++) {
        int currentValue = arr[i];
        int previousValue = currentValue - difference;
        int previousIndex = previousValue + 10000; // Shift to non-negative index
        int currentIndex = currentValue + 10000;   // Shift to non-negative index

        dp[currentIndex] = dp[previousIndex] + 1;
        if (dp[currentIndex] > maxLength) {
            maxLength = dp[currentIndex];
        }
    }

    free(dp);
    return maxLength;       
}
