// Source: https://leetcode.com/problems/minimum-absolute-sum-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integer arrays nums1 and nums2, both of length n.
//
// The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).
//
// You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.
//
// Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.
//
// |x| is defined as:
//
//
// 	x if x >= 0, or
// 	-x if x < 0.
//
// Example:
// Input: nums1 = [1,7,5], nums2 = [2,3,5]
// Output: 3
// Explanation: There are two possible optimal solutions:
// - Replace the second element with the first: [1,7,5] => [1,1,5], or
// - Replace the second element with the third: [1,7,5] => [1,5,5].
// Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
//
// Constraints:
// n == nums1.length
// 	n == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 105
//

int minAbsoluteSumDiff(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    #define MOD 1000000007

    int sorted[nums1Size];
    for (int i = 0; i < nums1Size; i++) {
        sorted[i] = nums1[i];
    }
    qsort(sorted, nums1Size, sizeof(int), (int (*)(const void*, const void*))strcmp);

    long totalDiff = 0;
    int maxReduction = 0;

    for (int i = 0; i < nums1Size; i++) {
        int diff = abs(nums1[i] - nums2[i]);
        totalDiff = (totalDiff + diff) % MOD;

        // Binary search for the closest value to nums2[i] in sorted
        int left = 0, right = nums1Size - 1;
        int bestDiff = diff;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int currentDiff = abs(sorted[mid] - nums2[i]);

            if (currentDiff < bestDiff) {
                bestDiff = currentDiff;
            }

            if (sorted[mid] < nums2[i]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        int reduction = diff - bestDiff;
        if (reduction > maxReduction) {
            maxReduction = reduction;
        }
    }

    return (totalDiff - maxReduction + MOD) % MOD;      
}
