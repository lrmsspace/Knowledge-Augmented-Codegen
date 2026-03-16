// Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
//
//
// 	The lengths of both arrays are n.
// 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
// 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
// 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
//
//
// Return the count of monotonic pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,2]
//
// Output: 4
//
// Explanation:
//
// The good pairs are:
//
//
// 	([0, 1, 1], [2, 2, 1])
// 	([0, 1, 2], [2, 2, 0])
// 	([0, 2, 2], [2, 1, 0])
// 	([1, 2, 2], [1, 1, 0])
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	1 <= nums[i] <= 1000
//

int countOfPairs(int* nums, int numsSize) {
    if (!nums || numsSize <= 0) return 0;
    const int MOD = 1000000007;
    int *dpInc = (int*)calloc(numsSize, sizeof(int));
    int *dpDec = (int*)calloc(numsSize, sizeof(int));
    if (!dpInc || !dpDec) {
        free(dpInc);
        free(dpDec);
        return 0;
    }

    for (int i = 0; i < numsSize; ++i) {
        dpInc[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (nums[j] <= nums[i]) {
                dpInc[i] = (dpInc[i] + dpInc[j]) % MOD;
            }
        }
    }

    for (int i = numsSize - 1; i >= 0; --i) {
        dpDec[i] = 1;
        for (int j = numsSize - 1; j > i; --j) {
            if (nums[j] <= nums[i]) {
                dpDec[i] = (dpDec[i] + dpDec[j]) % MOD;
            }
        }
    }

    int result = 0;
    for (int i = 0; i < numsSize; ++i) {
        result = (result + ((long long)dpInc[i] * dpDec[i]) % MOD) % MOD;
    }

    free(dpInc);
    free(dpDec);
    return result;      
}
