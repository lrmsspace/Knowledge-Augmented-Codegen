// Source: https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and an integer k.
//
// Return the maximum sum of a subarray of nums, such that the size of the subarray is divisible by k.
//
// Example:
// Input: nums = [1,2], k = 1
//
// Output: 3
//
// Explanation:
//
// The subarray [1, 2] with sum 3 has length equal to 2 which is divisible by 1.
//
// Constraints:
// 1 <= k <= nums.length <= 2 * 105
// 	-109 <= nums[i] <= 109
//

long long maxSubarraySum(int* nums, int numsSize, int k) {
    long long prefixSum[numsSize + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    long long minPrefixSum[k];
    for (int i = 0; i < k; i++) {
        minPrefixSum[i] = __LONG_LONG_MAX__;
    }

    long long maxSum = -__LONG_LONG_MAX__;
    for (int i = 0; i <= numsSize; i++) {
        int modIndex = i % k;
        if (prefixSum[i] - minPrefixSum[modIndex] > maxSum) {
            maxSum = prefixSum[i] - minPrefixSum[modIndex];
        }
        if (prefixSum[i] < minPrefixSum[modIndex]) {
            minPrefixSum[modIndex] = prefixSum[i];
        }
    }

    return maxSum;      
}
