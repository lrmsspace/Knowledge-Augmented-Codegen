// Source: https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// A split of an integer array is good if:
//
//
// 	The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
// 	The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
//
//
// Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,1,1]
// Output: 1
// Explanation: The only good way to split nums is [1] [1] [1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 104
//

int waysToSplit(int* nums, int numsSize) {
    int MOD = 1e9 + 7;
    long long prefixSum[numsSize + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    long long totalWays = 0;
    for (int i = 1; i <= numsSize - 2; i++) {
        long long leftSum = prefixSum[i];

        // Binary search for the minimum index j such that prefixSum[j] >= 2 * leftSum
        int low = i + 1, high = numsSize - 1, minJ = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (prefixSum[mid] >= 2 * leftSum) {
                minJ = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // Binary search for the maximum index j such that prefixSum[j] <= (totalSum + leftSum) / 2
        low = i + 1, high = numsSize - 1;
        int maxJ = -1;
        long long totalSum = prefixSum[numsSize];
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (prefixSum[mid] <= (totalSum + leftSum) / 2) {
                maxJ = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (minJ != -1 && maxJ != -1 && maxJ >= minJ) {
            totalWays = (totalWays + (maxJ - minJ + 1)) % MOD;
        }
    }

    return (int)totalWays;      
}
