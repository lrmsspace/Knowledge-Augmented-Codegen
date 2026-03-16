// Source: https://leetcode.com/problems/maximize-greatness-of-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. You are allowed to permute nums into a new array perm of your choosing.
//
// We define the greatness of nums be the number of indices 0 <= i < nums.length for which perm[i] > nums[i].
//
// Return the maximum possible greatness you can achieve after permuting nums.
//
// Example:
// Input: nums = [1,3,5,2,1,3,1]
// Output: 4
// Explanation: One of the optimal rearrangements is perm = [2,5,1,3,3,1,1].
// At indices = 0, 1, 3, and 4, perm[i] > nums[i]. Hence, we return 4.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximizeGreatness(int* nums, int numsSize) {
    // Sort the array using a simple comparison-based sort (e.g., quicksort, mergesort).
    // Here, we will implement a simple mergesort for clarity.
    void merge(int* arr, int* aux, int left, int mid, int right) {
        int i = left;     // Starting index for left subarray
        int j = mid + 1;  // Starting index for right subarray
        int k = left;     // Starting index to be sorted

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                aux[k++] = arr[i++];
            } else {
                aux[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            aux[k++] = arr[i++];
        }

        while (j <= right) {
            aux[k++] = arr[j++];
        }

        for (i = left; i <= right; i++) {
            arr[i] = aux[i];
        }
    }

    void mergeSort(int* arr, int* aux, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, aux, left, mid);
            mergeSort(arr, aux, mid + 1, right);
            merge(arr, aux, left, mid, right);
        }
    }

    int* aux = (int*)malloc(numsSize * sizeof(int));
    mergeSort(nums, aux, 0, numsSize - 1);
    free(aux);

    // Now calculate the maximum greatness
    int greatness = 0;
    int j = 0;

    for (int i = 0; i < numsSize; i++) {
        while (j < numsSize && nums[j] <= nums[i]) {
            j++;
        }
        if (j < numsSize) {
            greatness++;
            j++;
        }
    }

    return greatness;       
}
