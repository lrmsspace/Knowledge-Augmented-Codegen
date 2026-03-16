// Source: https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/   |   Difficulty: Medium
//
// Problem Description:
// The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the largest pair sum in a list of pairs.
//
//
// 	For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.
//
//
// Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:
//
//
// 	Each element of nums is in exactly one pair, and
// 	The maximum pair sum is minimized.
//
//
// Return the minimized maximum pair sum after optimally pairing up the elements.
//
// Example:
// Input: nums = [3,5,2,3]
// Output: 7
// Explanation: The elements can be paired up into pairs (3,3) and (5,2).
// The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	n is even.
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.



int minPairSum(int* nums, int numsSize){
    // Helper function: Mergesort implementation
    void merge(int* arr, int* aux, int left, int mid, int right) {
        int i = left;    // Starting index for left subarray
        int j = mid + 1; // Starting index for right subarray
        int k = left;    // Starting index to be sorted

        // Copy data to auxiliary array
        for (int idx = left; idx <= right; idx++) {
            aux[idx] = arr[idx];
        }

        while (i <= mid && j <= right) {
            if (aux[i] <= aux[j]) {
                arr[k++] = aux[i++];
            } else {
                arr[k++] = aux[j++];
            }
        }

        while (i <= mid) {
            arr[k++] = aux[i++];
        }
        // No need to copy the second half since it's already in place
    }

    void mergeSort(int* arr, int* aux, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, aux, left, mid);
            mergeSort(arr, aux, mid + 1, right);
            merge(arr, aux, left, mid, right);
        }
    }

    // Main logic to minimize the maximum pair sum
    int* aux = (int*)malloc(numsSize * sizeof(int));
    mergeSort(nums, aux, 0, numsSize - 1);
    free(aux);

    int maxPairSum = 0;
    for (int i = 0; i < numsSize / 2; i++) {
        int pairSum = nums[i] + nums[numsSize - 1 - i];
        if (pairSum > maxPairSum) {
            maxPairSum = pairSum;
        }
    }

    return maxPairSum;
}
