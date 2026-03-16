// Source: https://leetcode.com/problems/rectangle-overlap/   |   Difficulty: Easy
//
// Problem Description:
// An axis-aligned rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) is the coordinate of its bottom-left corner, and (x2, y2) is the coordinate of its top-right corner. Its top and bottom edges are parallel to the X-axis, and its left and right edges are parallel to the Y-axis.
//
// Two rectangles overlap if the area of their intersection is positive. To be clear, two rectangles that only touch at the corner or edges do not overlap.
//
// Given two axis-aligned rectangles rec1 and rec2, return true if they overlap, otherwise return false.
//
// Example:
// Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
// Output: true
//
// Constraints:
// rec1.length == 4
// 	rec2.length == 4
// 	-109 <= rec1[i], rec2[i] <= 109
// 	rec1 and rec2 represent a valid rectangle with a non-zero area.
//
// Helpful references (internal KB):
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Finding intersection of two segments (geometry, interval, simulation, interval-scheduling)
//   • When to use: When determining if two line segments in 2D space cross, touch, or overlap, and to find the nature of their intersection (point, segment, or empty).
//   • Idea: This algorithm determines if two line segments intersect and calculates their intersection point or segment. It typically involves checking for orientation changes and handling special cases like collinearity, with an O(1) time complexity.
//   • Invariants: The bounding boxes of the two segments must overlap for an intersection to be possible.; If segments are collinear, their intersection is either empty, a point, or a sub-segment.
//   • Tips: Use a bounding box check first for early exit optimization.; Handle collinear segments as a distinct special case.
//   • Pitfalls: Incorrectly handling parallel or perfectly collinear segments.; Floating point inaccuracies leading to false positives or negatives.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isRectangleOverlap(int[] rec1, int[] rec2) {
        // Check if one rectangle is to the left of the other
        if (rec1[2] <= rec2[0] || rec2[2] <= rec1[0]) {
            return false;
        }
        // Check if one rectangle is above the other
        if (rec1[3] <= rec2[1] || rec2[3] <= rec1[1]) {
            return false;
        }
        // If neither of the above conditions are true, the rectangles overlap
        return true;            
    }
}
