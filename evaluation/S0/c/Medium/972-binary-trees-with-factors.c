// Source: https://leetcode.com/problems/binary-trees-with-factors/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
//
// We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.
//
// Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.
//
// Example:
// Input: arr = [2,4]
// Output: 3
// Explanation: We can make these trees: [2], [4], [4, 2, 2]
//
// Constraints:
// 1 <= arr.length <= 1000
// 	2 <= arr[i] <= 109
// 	All the values of arr are unique.
//

int numFactoredBinaryTrees(int* arr, int arrSize) {
    #define MOD 1000000007
    int dp[arrSize];
    for (int i = 0; i < arrSize; i++) {
        dp[i] = 1;
    }
    qsort(arr, arrSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] % arr[j] == 0) {
                int right = arr[i] / arr[j];
                int leftIndex = -1;
                // Binary search for right
                int low = j, high = arrSize - 1;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    if (arr[mid] == right) {
                        leftIndex = mid;
                        break;
                    } else if (arr[mid] < right) {
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }
                if (leftIndex != -1) {
                    dp[i] = (dp[i] + (long long)dp[j] * dp[leftIndex]) % MOD;
                }
            }
        }
    }
    long long result = 0;
    for (int i = 0; i < arrSize; i++) {
        result = (result + dp[i]) % MOD;
    }
    return (int)result;     
}
