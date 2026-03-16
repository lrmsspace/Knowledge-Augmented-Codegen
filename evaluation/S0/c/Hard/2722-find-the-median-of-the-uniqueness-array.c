// Source: https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The uniqueness array of nums is the sorted array that contains the number of distinct elements of all the subarrays of nums. In other words, it is a sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
//
// Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at index i and ends at index j.
//
// Return the median of the uniqueness array of nums.
//
// Note that the median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the smaller of the two values is taken.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 1
//
// Explanation:
//
// The uniqueness array of nums is [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])] which is equal to [1, 1, 1, 2, 2, 3]. The uniqueness array has a median of 1. Therefore, the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

int medianOfUniquenessArray(int* nums, int numsSize) {
    if (!nums || numsSize <= 0) return 0;

    int maxVal = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }

    int *freq = (int*)calloc(maxVal + 1, sizeof(int));
    if (!freq) return 0;

    long long totalSubarrays = ((long long)numsSize * (numsSize + 1)) / 2;
    long long medianPos = (totalSubarrays + 1) / 2; // position of the median in sorted order
    long long count = 0;
    int median = 0;

    for (int start = 0; start < numsSize; ++start) {
        memset(freq, 0, (maxVal + 1) * sizeof(int));
        int distinctCount = 0;

        for (int end = start; end < numsSize; ++end) {
            if (freq[nums[end]] == 0) {
                distinctCount++;
            }
            freq[nums[end]]++;

            count++;
            if (count == medianPos) {
                median = distinctCount;
                free(freq);
                return median;
            }
        }
    }

    free(freq);
    return median;      
}
