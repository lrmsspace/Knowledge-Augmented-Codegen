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
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isRectangleOverlap(int[] rec1, int[] rec2) {
        // Two rectangles do not overlap if one is to the left of the other or one is above the other.
        // Check if rec1 is to the left of rec2
        if (rec1[2] <= rec2[0]) {
            return false;
        }
        // Check if rec1 is to the right of rec2
        if (rec1[0] >= rec2[2]) {
            return false;
        }
        // Check if rec1 is above rec2
        if (rec1[1] >= rec2[3]) {
            return false;
        }
        // Check if rec1 is below rec2
        if (rec1[3] <= rec2[1]) {
            return false;
        }
        
        // If none of the above conditions are true, the rectangles overlap
        return true;            
    }
}
