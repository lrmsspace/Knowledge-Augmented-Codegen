// Source: https://leetcode.com/problems/count-of-range-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and two integers lower and upper, return the number of range sums that lie in [lower, upper] inclusive.
//
// Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j inclusive, where i <= j.
//
// Example:
// Input: nums = [-2,5,-1], lower = -2, upper = 2
// Output: 3
// Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
// 	-105 <= lower <= upper <= 105
// 	The answer is guaranteed to fit in a 32-bit integer.
//

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long *prefixSums = (long*)malloc((numsSize + 1) * sizeof(long));
    if (!prefixSums) return 0;
    prefixSums[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }

    int count = 0;

    // Helper function for merge sort and counting
    void mergeSortAndCount(long* sums, int left, int right) {
        if (right - left <= 1) return;
        int mid = left + (right - left) / 2;
        mergeSortAndCount(sums, left, mid);
        mergeSortAndCount(sums, mid, right);

        int j = mid, k = mid;
        for (int i = left; i < mid; ++i) {
            while (j < right && sums[j] - sums[i] < lower) j++;
            while (k < right && sums[k] - sums[i] <= upper) k++;
            count += k - j;
        }

        // Merge step
        long* temp = (long*)malloc((right - left) * sizeof(long));
        if (!temp) return; // allocation failure, but continue gracefully
        int p1 = left, p2 = mid, idx = 0;
        while (p1 < mid && p2 < right) {
            if (sums[p1] <= sums[p2]) {
                temp[idx++] = sums[p1++];
            } else {
                temp[idx++] = sums[p2++];
            }
        }
        while (p1 < mid) temp[idx++] = sums[p1++];
        while (p2 < right) temp[idx++] = sums[p2++];
        memcpy(sums + left, temp, (right - left) * sizeof(long));
        free(temp);
    }

    mergeSortAndCount(prefixSums, 0, numsSize + 1);
    free(prefixSums);
    return count;       
}
