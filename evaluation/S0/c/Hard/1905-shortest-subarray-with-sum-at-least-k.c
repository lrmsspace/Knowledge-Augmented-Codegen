// Source: https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1], k = 1
// Output: 1
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
// 	1 <= k <= 109
//

int shortestSubarray(int* nums, int numsSize, int k) {
    int *prefixSums = (int*)malloc((numsSize + 1) * sizeof(int));
    if (!prefixSums) return -1;

    prefixSums[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }

    int minLength = numsSize + 1;
    int *deque = (int*)malloc((numsSize + 1) * sizeof(int));
    if (!deque) {
        free(prefixSums);
        return -1;
    }
    int front = 0, back = 0;

    for (int i = 0; i <= numsSize; ++i) {
        while (front < back && prefixSums[i] - prefixSums[deque[front]] >= k) {
            minLength = (i - deque[front] < minLength) ? (i - deque[front]) : minLength;
            front++;
        }
        while (front < back && prefixSums[i] <= prefixSums[deque[back - 1]]) {
            back--;
        }
        deque[back++] = i;
    }

    free(prefixSums);
    free(deque);

    return (minLength <= numsSize) ? minLength : -1;        
}
