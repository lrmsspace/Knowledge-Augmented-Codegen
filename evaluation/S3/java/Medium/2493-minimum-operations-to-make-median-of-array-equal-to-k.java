// Source: https://leetcode.com/problems/minimum-operations-to-make-median-of-array-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a non-negative integer k. In one operation, you can increase or decrease any element by 1.
//
// Return the minimum number of operations needed to make the median of nums equal to k.
//
// The median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the larger of the two values is taken.
//
// Example:
// Input: nums = [2,5,6,8,5], k = 4
//
// Output: 2
//
// Explanation:
//
// We can subtract one from nums[1] and nums[4] to obtain [2, 4, 6, 8, 4]. The median of the resulting array is equal to k.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// -  
// Kth order statistic in O(N) (array, quickselect)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without fully sorting the entire data structure. It's particularly useful for large datasets where a full sort is too slow.
//   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list. It uses a divide-and-conquer approach similar to Quicksort, but only recurses on one side, achieving an average time complexity of O(N).
//   • Invariants: All elements to the left of the pivot are less than or equal to the pivot's value.; All elements to the right of the pivot are greater than or equal to the pivot's value.
//   • Tips: Choose a good pivot strategy, such as a random pivot, to minimize the chance of worst-case performance.; Handle duplicate elements carefully during the partitioning step to ensure correctness.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Deep recursion without tail call optimization can cause stack overflow errors.
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long minOperationsToMakeMedianK(int[] nums, int k) {
        int n = nums.length;
        int medianIndex = (n - 1) / 2; // Index of the median in a sorted array
        long operations = 0;

        for (int num : nums) {
            if (num < k) {
                operations += (k - num); // Increase num to k
            } else if (num > k) {
                operations += (num - k); // Decrease num to k
            }
        }

        return operations;          
    }
}
