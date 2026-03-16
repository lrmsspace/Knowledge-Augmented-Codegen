// Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// The distinct count of a subarray of nums is defined as:
//
//
// 	Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
//
//
// Return the sum of the squares of distinct counts of all subarrays of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,1]
// Output: 15
// Explanation: Six possible subarrays are:
// [1]: 1 distinct value
// [2]: 1 distinct value
// [1]: 1 distinct value
// [1,2]: 2 distinct values
// [2,1]: 2 distinct values
// [1,2,1]: 2 distinct values
// The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

int sumCounts(int* nums, int numsSize) {
    const int MOD = 1000000007;
    int maxVal = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    int *lastPos = (int*)calloc(maxVal + 1, sizeof(int));
    if (!lastPos) return 0;

    long long result = 0;
    long long currSum = 0;
    int left = 0;

    for (int right = 0; right < numsSize; ++right) {
        int val = nums[right];
        int last = lastPos[val];
        lastPos[val] = right + 1; /* store position + 1 to differentiate from default 0 */

        if (last > 0) {
            /* Remove contributions from subarrays that included the previous occurrence */
            for (int i = left; i < last - 1; ++i) {
                int distinctCount = right - i;
                currSum = (currSum - (long long)(distinctCount + 1) * (distinctCount + 1) % MOD + MOD) % MOD;
            }
            left = last - 1;
        }

        /* Add contributions from new subarrays ending at 'right' */
        for (int i = left; i <= right; ++i) {
            int distinctCount = right - i + 1;
            currSum = (currSum + (long long)(distinctCount) * (distinctCount) % MOD) % MOD;
        }

        result = (result + currSum) % MOD;
    }

    free(lastPos);
    return (int)result;     
}
