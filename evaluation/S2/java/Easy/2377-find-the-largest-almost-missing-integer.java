// Source: https://leetcode.com/problems/find-the-largest-almost-missing-integer/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.
//
// Return the largest almost missing integer from nums. If no such integer exists, return -1.
// A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: nums = [3,9,2,1,7], k = 3
//
// Output: 7
//
// Explanation:
//
//
// 	1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
// 	2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
// 	3 appears in 1 subarray of size 3: [3, 9, 2].
// 	7 appears in 1 subarray of size 3: [2, 1, 7].
// 	9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].
//
//
// We return 7 since it is the largest integer that appears in exactly one subarray of size k.
//
// Constraints:
// 1 <= nums.length <= 50
// 	0 <= nums[i] <= 50
// 	1 <= k <= nums.length
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int largestInteger(int[] nums, int k) {
        int n = nums.length;
        Map<Integer, Integer> countMap = new HashMap<>();

        // Count the occurrences of each integer in subarrays of size k
        for (int i = 0; i <= n - k; i++) {
            Set<Integer> uniqueElements = new HashSet<>();
            for (int j = i; j < i + k; j++) {
                uniqueElements.add(nums[j]);
            }
            for (int num : uniqueElements) {
                countMap.put(num, countMap.getOrDefault(num, 0) + 1);
            }
        }

        int largestAlmostMissing = -1;

        // Find the largest integer that appears in exactly one subarray of size k
        for (Map.Entry<Integer, Integer> entry : countMap.entrySet()) {
            if (entry.getValue() == 1) {
                largestAlmostMissing = Math.max(largestAlmostMissing, entry.getKey());
            }
        }

        return largestAlmostMissing;            
    }
}
