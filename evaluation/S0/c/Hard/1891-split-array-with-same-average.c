// Source: https://leetcode.com/problems/split-array-with-same-average/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums.
//
// You should move each element of nums into one of the two arrays A and B such that A and B are non-empty, and average(A) == average(B).
//
// Return true if it is possible to achieve that and false otherwise.
//
// Note that for an array arr, average(arr) is the sum of all the elements of arr over the length of arr.
//
// Example:
// Input: nums = [1,2,3,4,5,6,7,8]
// Output: true
// Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have an average of 4.5.
//
// Constraints:
// 1 <= nums.length <= 30
// 	0 <= nums[i] <= 104
//

bool splitArraySameAverage(int* nums, int numsSize) {
    int totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum += nums[i];
    }

    /* dp[i][j] indicates whether it's possible to get sum j using i elements */
    int dp[numsSize + 1][totalSum + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int numIdx = 0; numIdx < numsSize; ++numIdx) {
        int num = nums[numIdx];
        for (int i = numsSize - 1; i >= 0; --i) {
            for (int j = totalSum - num; j >= 0; --j) {
                if (dp[i][j]) {
                    dp[i + 1][j + num] = 1;
                }
            }
        }
    }

    for (int lenA = 1; lenA <= numsSize / 2; ++lenA) {
        if ((totalSum * lenA) % numsSize != 0) continue;
        int sumA = (totalSum * lenA) / numsSize;
        if (dp[lenA][sumA]) return 1;
    }

    return 0;       
}
