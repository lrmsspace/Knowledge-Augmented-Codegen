// Source: https://leetcode.com/problems/longest-mountain-in-array/   |   Difficulty: Medium
//
// Problem Description:
// You may recall that an array arr is a mountain array if and only if:
//
//
// 	arr.length >= 3
// 	There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
// 	
// 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
// 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
// 	
// 	
//
//
// Given an integer array arr, return the length of the longest subarray, which is a mountain. Return 0 if there is no mountain subarray.
//
// Example:
// Input: arr = [2,1,4,7,3,2,5]
// Output: 5
// Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 104
//
//
//  
// Follow up:
//
//
// 	Can you solve it using only one pass?
// 	Can you solve it in O(1) space?
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Range Minimum Query (array, tree, lca)
//   • When to use: Use when needing to find the minimum element within various specified ranges of a static array efficiently, especially when many queries are expected after initial preprocessing.
//   • Idea: Range Minimum Query (RMQ) finds the minimum value in a given contiguous subsegment of an array. It typically involves preprocessing the array to achieve O(1) or O(log N) query time, with preprocessing in O(N log N) or O(N).
//   • Invariants: For a Sparse Table `st[i][j]`, `st[i][j]` stores the minimum in the range `[i, i + 2^j - 1]`.; During a query `[L, R]`, the chosen blocks `[L, L + 2^k - 1]` and `[R - 2^k + 1, R]` completely cover the target range.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) preprocessing.; Segment Trees provide O(log N) query and update times, suitable for dynamic arrays.
//   • Pitfalls: Sparse Tables do not support updates efficiently; they are primarily for static data.; Off-by-one errors are common when calculating range indices or log values for segment lengths.
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
    public int longestMountain(int[] arr) {
        int n = arr.length;
        int longest = 0;
        int i = 1;

        while (i < n - 1) {
            // Check if arr[i] is a peak
            if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
                int left = i - 1;
                int right = i + 1;

                // Expand to the left
                while (left > 0 && arr[left] > arr[left - 1]) {
                    left--;
                }

                // Expand to the right
                while (right < n - 1 && arr[right] > arr[right + 1]) {
                    right++;
                }

                // Calculate the length of the mountain
                int currentMountainLength = right - left + 1;
                longest = Math.max(longest, currentMountainLength);

                // Move i to the end of this mountain
                i = right;
            } else {
                i++;
            }
        }

        return longest;         
    }
}
