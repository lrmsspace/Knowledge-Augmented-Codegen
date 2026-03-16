// Source: https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers k and numOperations.
//
// You must perform an operation numOperations times on nums, where in each operation you:
//
//
//  Select an index i that was not selected in any previous operations.
//  Add an integer in the range [-k, k] to nums[i].
//
//
// Return the maximum possible frequency of any element in nums after performing the operations.
//
// Example:
// Input: nums = [1,4,5], k = 1, numOperations = 2
//
// Output: 2
//
// Explanation:
//
// We can achieve a maximum frequency of two by:
//
//
//  Adding 0 to nums[1], after which nums becomes [1, 4, 5].
//  Adding -1 to nums[2], after which nums becomes [1, 4, 4].
//
// Constraints:
// 1 <= nums.length <= 105
//  1 <= nums[i] <= 109
//  0 <= k <= 109
//  0 <= numOperations <= nums.length
//

int maxFrequency(int* nums, int numsSize, int k, int numOperations) {
    if (numsSize == 0) return 0;

    // Sort the array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    long long total = 0;
    int left = 0, result = 1;

    for (int right = 0; right < numsSize; ++right) {
        total += nums[right];

        while ((long long)(nums[right]) * (right - left + 1) - total > (long long)k * numOperations) {
            total -= nums[left];
            left++;
        }

        result = (right - left + 1) > result ? (right - left + 1) : result;
    }

    return result;      
}
