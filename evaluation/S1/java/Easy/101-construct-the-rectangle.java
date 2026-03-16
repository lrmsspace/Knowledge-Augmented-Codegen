// Source: https://leetcode.com/problems/construct-the-rectangle/   |   Difficulty: Easy
//
// Problem Description:
// A web developer needs to know how to design a web page's size. So, given a specific rectangular web page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:
//
//
// 	The area of the rectangular web page you designed must equal to the given target area.
// 	The width W should not be larger than the length L, which means L >= W.
// 	The difference between length L and width W should be as small as possible.
//
//
// Return an array [L, W] where L and W are the length and width of the web page you designed in sequence.
//
// Example:
// Input: area = 4
// Output: [2,2]
// Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1]. 
// But according to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not optimal compared to [2,2]. So the length L is 2, and the width W is 2.
//
// Constraints:
// 1 <= area <= 107
//
// Helpful references (internal KB):
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] constructRectangle(int area) {
        int w = (int) Math.sqrt(area);
        while (area % w != 0) {
            w--;
        }
        int l = area / w;
        return new int[]{l, w};         
    }
}
