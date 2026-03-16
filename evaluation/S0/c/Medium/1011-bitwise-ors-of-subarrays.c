// Source: https://leetcode.com/problems/bitwise-ors-of-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.
//
// The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: arr = [0]
// Output: 1
// Explanation: There is only one possible result: 0.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	0 <= arr[i] <= 109
//

int subarrayBitwiseORs(int* arr, int arrSize) {
    int res[32 * arrSize];
    int resSize = 0;

    int cur[32 * arrSize];
    int curSize = 0;

    for (int i = 0; i < arrSize; ++i) {
        int next[32 * arrSize];
        int nextSize = 0;

        next[nextSize++] = arr[i];
        for (int j = 0; j < curSize; ++j) {
            int val = cur[j] | arr[i];
            if (val != next[nextSize - 1]) {
                next[nextSize++] = val;
            }
        }

        for (int j = 0; j < nextSize; ++j) {
            int val = next[j];
            int k;
            for (k = 0; k < resSize; ++k) {
                if (res[k] == val) {
                    break;
                }
            }
            if (k == resSize) {
                res[resSize++] = val;
            }
        }

        for (int j = 0; j < nextSize; ++j) {
            cur[j] = next[j];
        }
        curSize = nextSize;
    }

    return resSize;     
}
