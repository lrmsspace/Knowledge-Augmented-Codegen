// Source: https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Starting with score = 0, apply the following algorithm:
//
//
// 	Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
// 	Add the value of the chosen integer to score.
// 	Mark the chosen element and its two adjacent elements if they exist.
// 	Repeat until all the array elements are marked.
//
//
// Return the score you get after applying the above algorithm.
//
// Example:
// Input: nums = [2,1,3,4,5,2]
// Output: 7
// Explanation: We mark the elements as follows:
// - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
// - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
// - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
// Our score is 1 + 2 + 4 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long findScore(int* nums, int numsSize) {
    long long score = 0;
    int marked[numsSize];
    for (int i = 0; i < numsSize; i++) {
        marked[i] = 0;
    }

    for (int i = 0; i < numsSize; i++) {
        int minIndex = -1;
        for (int j = 0; j < numsSize; j++) {
            if (!marked[j] && (minIndex == -1 || nums[j] < nums[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != -1) {
            score += nums[minIndex];
            marked[minIndex] = 1;
            if (minIndex > 0) {
                marked[minIndex - 1] = 1;
            }
            if (minIndex < numsSize - 1) {
                marked[minIndex + 1] = 1;
            }
        }
    }

    return score;       
}
