// Source: https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).
//
// Return the maximum absolute sum of any (possibly empty) subarray of nums.
//
// Note that abs(x) is defined as follows:
//
//
// 	If x is a negative integer, then abs(x) = -x.
// 	If x is a non-negative integer, then abs(x) = x.
//
// Example:
// Input: nums = [1,-3,2,3,-4]
// Output: 5
// Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

int maxAbsoluteSum(int* nums, int numsSize) {
    int max_sum = 0;
    int min_sum = 0;
    int current_max = 0;
    int current_min = 0;

    for (int i = 0; i < numsSize; i++) {
        current_max += nums[i];
        current_min += nums[i];

        if (current_max < 0) {
            current_max = 0;
        }
        if (current_min > 0) {
            current_min = 0;
        }

        if (current_max > max_sum) {
            max_sum = current_max;
        }
        if (current_min < min_sum) {
            min_sum = current_min;
        }
    }

    return (max_sum > -min_sum) ? max_sum : -min_sum;       
}
