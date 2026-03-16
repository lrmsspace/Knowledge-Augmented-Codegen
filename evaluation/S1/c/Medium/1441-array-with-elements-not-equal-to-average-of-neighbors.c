// Source: https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of distinct integers. You want to rearrange the elements in the array such that every element in the rearranged array is not equal to the average of its neighbors.
//
// More formally, the rearranged array should have the property such that for every i in the range 1 <= i < nums.length - 1, (nums[i-1] + nums[i+1]) / 2 is not equal to nums[i].
//
// Return any rearrangement of nums that meets the requirements.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: [1,2,4,5,3]
// Explanation:
// When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
// When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
// When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rearrangeArray(int* nums, int numsSize, int* returnSize) {
    // Sort the array using a simple O(N log N) sorting algorithm (e.g., mergesort)
    void merge(int* arr, int* aux, int left, int mid, int right) {
        int i = left;     // Starting index for left subarray
        int j = mid + 1;  // Starting index for right subarray
        int k = left;     // Starting index to be merged

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

    // Rearrange the sorted array
    int* result = (int*)malloc(numsSize * sizeof(int));
    int left = 0;
    int right = numsSize - 1;
    int index = 0;

    while (left <= right) {
        if (index % 2 == 0) {
            result[index++] = nums[left++];
        } else {
            result[index++] = nums[right--];
        }
    }

    *returnSize = numsSize;
    return result;      
}
