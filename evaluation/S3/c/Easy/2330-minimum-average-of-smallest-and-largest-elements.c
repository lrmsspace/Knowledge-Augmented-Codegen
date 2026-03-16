// Source: https://leetcode.com/problems/minimum-average-of-smallest-and-largest-elements/   |   Difficulty: Easy
//
// Problem Description:
// You have an array of floating point numbers averages which is initially empty. You are given an array nums of n integers where n is even.
//
// You repeat the following procedure n / 2 times:
//
//
// 	Remove the smallest element, minElement, and the largest element maxElement, from nums.
// 	Add (minElement + maxElement) / 2 to averages.
//
//
// Return the minimum element in averages.
//
// Example:
// Input: nums = [7,8,3,4,15,13,4,1]
//
// Output: 5.5
//
// Explanation:
//
//
// 	
// 		
// 			step
// 			nums
// 			averages
// 		
// 		
// 			0
// 			[7,8,3,4,15,13,4,1]
// 			[]
// 		
// 		
// 			1
// 			[7,8,3,4,13,4]
// 			[8]
// 		
// 		
// 			2
// 			[7,8,4,4]
// 			[8,8]
// 		
// 		
// 			3
// 			[7,4]
// 			[8,8,6]
// 		
// 		
// 			4
// 			[]
// 			[8,8,6,5.5]
// 		
// 	
//
// The smallest element of averages, 5.5, is returned.
//
// Constraints:
// 2 <= n == nums.length <= 50
// 	n is even.
// 	1 <= nums[i] <= 50
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double minimumAverage(int* nums, int numsSize) {
    // Sort the array using a simple sorting algorithm (e.g., bubble sort)
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                // Swap nums[j] and nums[j + 1]
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    double minAverage = (nums[0] + nums[numsSize - 1]) / 2.0;

    for (int i = 1; i < numsSize / 2; i++) {
        double average = (nums[i] + nums[numsSize - 1 - i]) / 2.0;
        if (average < minAverage) {
            minAverage = average;
        }
    }

    return minAverage;      
}
