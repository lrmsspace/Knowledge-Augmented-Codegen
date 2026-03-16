// Source: https://leetcode.com/problems/perfect-rectangle/   |   Difficulty: Hard
//
// Problem Description:
// Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
//
// Return true if all the rectangles together form an exact cover of a rectangular region.
//
// Example:
// Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
// Output: true
// Explanation: All 5 rectangles together form an exact cover of a rectangular region.
//
// Constraints:
// 1 <= rectangles.length <= 2 * 104
// 	rectangles[i].length == 4
// 	-105 <= xi < ai <= 105
// 	-105 <= yi < bi <= 105
//
// Helpful references (internal KB):
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
// - Half-plane intersection (geometry, simulation)
//   • When to use: When you need to find the common region defined by a set of half-planes, or determine if such a region exists. It's particularly useful for checking if the intersection is empty.
//   • Idea: This method finds the intersection of N half-planes by checking all O(N^2) pairwise line intersections. Each intersection point is then verified against all N half-planes, resulting in an O(N^3) time complexity.
//   • Invariants: Each candidate vertex is an intersection of two half-plane boundary lines.; Any point included in the final intersection region satisfies all given half-plane constraints.
//   • Tips: The vertices of the resulting convex polygon are always intersection points of the boundary lines.; Can be used to check if the intersection region is empty.
//   • Pitfalls: High time complexity of O(N^3) makes it inefficient for large N.; Numerical precision issues when calculating intersection points and checking containment.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isRectangleCover(int[][] rectangles) {
        int minX = Integer.MAX_VALUE, minY = Integer.MAX_VALUE;
        int maxX = Integer.MIN_VALUE, maxY = Integer.MIN_VALUE;
        int actualArea = 0;
        java.util.Set<String> pointSet = new java.util.HashSet<>();

        for (int[] rect : rectangles) {
            int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];

            minX = Math.min(minX, x1);
            minY = Math.min(minY, y1);
            maxX = Math.max(maxX, x2);
            maxY = Math.max(maxY, y2);

            actualArea += (x2 - x1) * (y2 - y1);

            String[] points = {
                x1 + "," + y1,
                x1 + "," + y2,
                x2 + "," + y1,
                x2 + "," + y2
            };

            for (String point : points) {
                if (!pointSet.add(point)) {
                    pointSet.remove(point);
                }
            }
        }

        int expectedArea = (maxX - minX) * (maxY - minY);
        if (actualArea != expectedArea) {
            return false;
        }

        String[] expectedPoints = {
            minX + "," + minY,
            minX + "," + maxY,
            maxX + "," + minY,
            maxX + "," + maxY
        };

        if (pointSet.size() != 4) {
            return false;
        }

        for (String point : expectedPoints) {
            if (!pointSet.contains(point)) {
                return false;
            }
        }

        return true;            
    }
}
