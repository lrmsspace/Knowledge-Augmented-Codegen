// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array points where points[i] = [xi, yi] represents the coordinates of a point on an infinite plane.
//
// Your task is to find the maximum area of a rectangle that:
//
//
// 	Can be formed using four of these points as its corners.
// 	Does not contain any other point inside or on its border.
// 	Has its edges parallel to the axes.
//
//
// Return the maximum area that you can obtain or -1 if no such rectangle is possible.
//
// Example:
// Input: points = [[1,1],[1,3],[3,1],[3,3]]
//
// Output: 4
//
// Explanation:
//
//
//
// We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
//
// Constraints:
// 1 <= points.length <= 10
// 	points[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given points are unique.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Lattice points inside non-lattice polygon (geometry, number, counting, recursion)
//   • When to use: Use this when you need to count integer coordinate points strictly inside a polygon whose vertices are not restricted to integer coordinates. It's suitable for problems requiring precise geometric counting with non-lattice boundaries.
//   • Idea: This algorithm counts lattice points within a polygon with arbitrary vertices by summing signed contributions from each edge. It reduces the problem to evaluating sums of floor functions, sum(floor(kx+b)), which is solved recursively, typically achieving logarithmic complexity per edge.
//   • Invariants: The sum sum(floor(kx+b)) correctly accumulates points below the current edge segment.; After coordinate transformations, the problem reduces to a sum over a non-negative range with non-negative k and b.
//   • Tips: Decompose the polygon into signed areas under each edge, similar to the shoelace formula.; Handle edge cases where k or b are negative by appropriate transformations.
//   • Pitfalls: Floating point precision issues when calculating k and b or during transformations.; Incorrectly handling boundary points (points on edges or vertices).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int calculateArea(int[] p1, int[] p2, int[] p3, int[] p4) {
        int length = Math.abs(p1[0] - p2[0]);
        int width = Math.abs(p1[1] - p3[1]);
        return length * width;
    }
    private boolean isValidRectangle(int[][] points, int i, int j, int k, int l) {
        java.util.Set<String> pointSet = new java.util.HashSet<>();
        for (int m = 0; m < points.length; m++) {
            if (m != i && m != j && m != k && m != l) {
                pointSet.add(points[m][0] + "," + points[m][1]);
            }
        }

        int xMin = Math.min(Math.min(points[i][0], points[j][0]), Math.min(points[k][0], points[l][0]));
        int xMax = Math.max(Math.max(points[i][0], points[j][0]), Math.max(points[k][0], points[l][0]));
        int yMin = Math.min(Math.min(points[i][1], points[j][1]), Math.min(points[k][1], points[l][1]));
        int yMax = Math.max(Math.max(points[i][1], points[j][1]), Math.max(points[k][1], points[l][1]));

        for (String p : pointSet) {
            String[] coords = p.split(",");
            int x = Integer.parseInt(coords[0]);
            int y = Integer.parseInt(coords[1]);
            if (xMin <= x && x <= xMax && yMin <= y && y <= yMax) {
                return false;
            }
        }
        return true;
    }
    public int maxRectangleArea(int[][] points) {
        int n = points.length;
        int maxArea = -1;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        int area = calculateArea(points[i], points[j], points[k], points[l]);
                        if (area > 0 && isValidRectangle(points, i, j, k, l)) {
                            maxArea = Math.max(maxArea, area);
                        }
                    }
                }
            }
        }

        return maxArea;         
    }
}
