// Source: https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays nums and andValues of length n and m respectively.
//
// The value of an array is equal to the last element of that array.
//
// You have to divide nums into m disjoint contiguous subarrays such that for the ith subarray [li, ri], the bitwise AND of the subarray elements is equal to andValues[i], in other words, nums[li] & nums[li + 1] & ... & nums[ri] == andValues[i] for all 1 <= i <= m, where & represents the bitwise AND operator.
//
// Return the minimum possible sum of the values of the m subarrays nums is divided into. If it is not possible to divide nums into m subarrays satisfying these conditions, return -1.
//
// Example:
// Input: nums = [1,4,3,3,2], andValues = [0,3,3,2]
//
// Output: 12
//
// Explanation:
//
// The only possible way to divide nums is:
//
//
// 	[1,4] as 1 & 4 == 0.
// 	[3] as the bitwise AND of a single element subarray is that element itself.
// 	[3] as the bitwise AND of a single element subarray is that element itself.
// 	[2] as the bitwise AND of a single element subarray is that element itself.
//
//
// The sum of the values for these subarrays is 4 + 3 + 3 + 2 = 12.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= m == andValues.length <= min(n, 10)
// 	1 <= nums[i] < 105
// 	0 <= andValues[j] < 105
//

int minimumValueSum(int* nums, int numsSize, int* andValues, int andValuesSize) {
    int INF = 1000000000;
    int dp[andValuesSize + 1];
    for (int i = 0; i <= andValuesSize; ++i) dp[i] = INF;
    dp[0] = 0;

    for (int i = 0, start = 0; i < andValuesSize; ++i) {
        int curr_and = -1;
        int min_last = INF;
        int found = 0;
        for (int j = start; j < numsSize; ++j) {
            curr_and &= nums[j];
            if (curr_and == andValues[i]) {
                found = 1;
                if (nums[j] < min_last) min_last = nums[j];
                if (i + 1 < andValuesSize) {
                    // prepare for next segment
                    if (dp[i] != INF && dp[i] + min_last < dp[i + 1]) {
                        dp[i + 1] = dp[i] + min_last;
                    }
                } else {
                    // last segment
                    if (dp[i] != INF && dp[i] + min_last < dp[i + 1]) {
                        dp[i + 1] = dp[i] + min_last;
                    }
                }
            }
            if (curr_and < andValues[i]) break; // cannot reach andValues[i] anymore
        }
        if (!found) return -1; // cannot form segment for andValues[i]
        // move start to the next position after the last segment
        start = numsSize - 1;
        for (int j = numsSize - 1; j >= 0; --j) {
            curr_and &= nums[j];
            if (curr_and == andValues[i]) {
                start = j + 1;
                break;
            }
            if (curr_and < andValues[i]) break;
        }
    }

    return dp[andValuesSize] == INF ? -1 : dp[andValuesSize];       
}
