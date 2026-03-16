// Source: https://leetcode.com/problems/number-of-distinct-averages/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums of even length.
//
// As long as nums is not empty, you must repetitively:
//
//
// 	Find the minimum number in nums and remove it.
// 	Find the maximum number in nums and remove it.
// 	Calculate the average of the two removed numbers.
//
//
// The average of two numbers a and b is (a + b) / 2.
//
//
// 	For example, the average of 2 and 3 is (2 + 3) / 2 = 2.5.
//
//
// Return the number of distinct averages calculated using the above process.
//
// Note that when there is a tie for a minimum or maximum number, any can be removed.
//
// Example:
// Input: nums = [4,1,4,0,3,5]
// Output: 2
// Explanation:
// 1. Remove 0 and 5, and the average is (0 + 5) / 2 = 2.5. Now, nums = [4,1,4,3].
// 2. Remove 1 and 4. The average is (1 + 4) / 2 = 2.5, and nums = [4,3].
// 3. Remove 3 and 4, and the average is (3 + 4) / 2 = 3.5.
// Since there are 2 distinct numbers among 2.5, 2.5, and 3.5, we return 2.
//
// Constraints:
// 2 <= nums.length <= 100
// 	nums.length is even.
// 	0 <= nums[i] <= 100
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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var distinctAverages = function(nums) {
    const averages = new Set(); // Set to store distinct averages
    while (nums.length > 0) { // Continue until the array is empty
        const min = Math.min(...nums); // Find the minimum number
        const max = Math.max(...nums); // Find the maximum number
        const average = (min + max) / 2; // Calculate the average of min and max
        averages.add(average); // Add the average to the set of distinct averages
        nums.splice(nums.indexOf(min), 1); // Remove the minimum number from the array
        nums.splice(nums.indexOf(max), 1); // Remove the maximum number from the array
    }
    return averages.size; // Return the number of distinct averages
};
