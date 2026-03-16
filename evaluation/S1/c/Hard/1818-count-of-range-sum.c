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
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    if (!nums || numsSize <= 0) return 0;

    long long *prefixSums = (long long*)malloc((numsSize + 1) * sizeof(long long));
    if (!prefixSums) return 0;

    prefixSums[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }

    int count = 0;

    void mergeSort(long long* s, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(s, left, mid);
        mergeSort(s, mid + 1, right);

        int jLow = mid + 1, jHigh = mid + 1;
        for (int i = left; i <= mid; ++i) {
            while (jLow <= right && s[jLow] - s[i] < lower) jLow++;
            while (jHigh <= right && s[jHigh] - s[i] <= upper) jHigh++;
            count += (jHigh - jLow);
        }

        long long* temp = (long long*)malloc((right - left + 1) * sizeof(long long));
        if (!temp) return;

        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right) {
            if (s[i] <= s[j]) {
                temp[k++] = s[i++];
            } else {
                temp[k++] = s[j++];
            }
        }
        while (i <= mid) {
            temp[k++] = s[i++];
        }
        while (j <= right) {
            temp[k++] = s[j++];
        }
        for (i = left, k = 0; i <= right; ++i, ++k) {
            s[i] = temp[k];
        }
        free(temp);
    }

    mergeSort(prefixSums, 0, numsSize);
    free(prefixSums);
    return count;       
}
