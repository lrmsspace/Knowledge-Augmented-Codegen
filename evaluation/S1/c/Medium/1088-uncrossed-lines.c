// Source: https://leetcode.com/problems/uncrossed-lines/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2. We write the integers of nums1 and nums2 (in the order they are given) on two separate horizontal lines.
//
// We may draw connecting lines: a straight line connecting two numbers nums1[i] and nums2[j] such that:
//
//
// 	nums1[i] == nums2[j], and
// 	the line we draw does not intersect any other connecting (non-horizontal) line.
//
//
// Note that a connecting line cannot intersect even at the endpoints (i.e., each number can only belong to one connecting line).
//
// Return the maximum number of connecting lines we can draw in this way.
//
// Example:
// Input: nums1 = [1,4,2], nums2 = [1,2,4]
// Output: 2
// Explanation: We can draw 2 uncrossed lines as in the diagram.
// We cannot draw 3 uncrossed lines, because the line from nums1[1] = 4 to nums2[2] = 4 will intersect the line from nums1[2]=2 to nums2[1]=2.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 500
// 	1 <= nums1[i], nums2[j] <= 2000
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Intersection Point of Lines (geometry, number, enumeration)
//   • When to use: When you need to find the exact coordinates where two lines meet in a 2D plane, or determine if they are parallel or coincident. This is useful for geometric problems involving line segments or polygons.
//   • Idea: This method calculates the coordinates of the intersection point of two lines, typically represented in general form (Ax + By + C = 0), by solving a system of linear equations. It has a constant time complexity, O(1), for each pair of lines.
//   • Invariants: The coefficients (a, b, c) for each line remain constant throughout the calculation.; If the determinant of the coefficient matrix is non-zero, a unique intersection point exists.
//   • Tips: Represent lines in a consistent form, like general form (Ax + By + C = 0) or slope-intercept (y = mx + b).; Handle edge cases for parallel and coincident lines explicitly to avoid division by zero.
//   • Pitfalls: Division by zero if lines are parallel or coincident without proper checks.; Floating-point precision errors can lead to incorrect intersection points or misidentification of parallel lines.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // This problem is equivalent to finding the length of the longest common subsequence (LCS)
    // between nums1 and nums2. We can use dynamic programming to solve this.

    // Create a 2D DP array to store lengths of longest common subsequences.
    int dp[nums1Size + 1][nums2Size + 1];

    // Initialize the DP array with zeros.
    for (int i = 0; i <= nums1Size; i++) {
        for (int j = 0; j <= nums2Size; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill the DP array.
    for (int i = 1; i <= nums1Size; i++) {
        for (int j = 1; j <= nums2Size; j++) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // Match found
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1]; // No match
            }
        }
    }

    // The bottom-right cell contains the length of the longest common subsequence.
    return dp[nums1Size][nums2Size];        
}
