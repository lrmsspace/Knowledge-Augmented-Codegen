// Source: https://leetcode.com/problems/closest-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer goal.
//
// You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).
//
// Return the minimum possible value of abs(sum - goal).
//
// Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.
//
// Example:
// Input: nums = [5,-7,3,5], goal = 6
// Output: 0
// Explanation: Choose the whole array as a subsequence, with a sum of 6.
// This is equal to the goal, so the absolute difference is 0.
//
// Constraints:
// 1 <= nums.length <= 40
// 	-107 <= nums[i] <= 107
// 	-109 <= goal <= 109
//

int minAbsDifference(int* nums, int numsSize, int goal) {
    int n1 = numsSize / 2;
    int n2 = numsSize - n1;
    int size1 = 1 << n1;
    int size2 = 1 << n2;
    int *sums1 = (int*)malloc(size1 * sizeof(int));
    int *sums2 = (int*)malloc(size2 * sizeof(int));
    if (!sums1 || !sums2) {
        free(sums1); free(sums2);
        return -1; /* allocation failure */
    }

    for (int i = 0; i < size1; ++i) {
        int sum = 0;
        for (int j = 0; j < n1; ++j) {
            if (i & (1 << j)) sum += nums[j];
        }
        sums1[i] = sum;
    }
    for (int i = 0; i < size2; ++i) {
        int sum = 0;
        for (int j = 0; j < n2; ++j) {
            if (i & (1 << j)) sum += nums[n1 + j];
        }
        sums2[i] = sum;
    }

    qsort(sums2, size2, sizeof(int), cmpInt);

    int minDiff = abs(goal);
    for (int i = 0; i < size1; ++i) {
        int complement = goal - sums1[i];
        int idx = lowerBound(sums2, size2, complement);
        if (idx < size2) {
            int diff = abs(sums1[i] + sums2[idx] - goal);
            if (diff < minDiff) minDiff = diff;
        }
        if (idx > 0) {
            int diff = abs(sums1[i] + sums2[idx - 1] - goal);
            if (diff < minDiff) minDiff = diff;
        }
    }
    free(sums1);
    free(sums2);
    return minDiff;
    
}
