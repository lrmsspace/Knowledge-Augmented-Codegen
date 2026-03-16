// Source: https://leetcode.com/problems/valid-boomerang/   |   Difficulty: Easy
//
// Problem Description:
// Given an array points where points[i] = [xi, yi] represents a point on the X-Y plane, return true if these points are a boomerang.
//
// A boomerang is a set of three points that are all distinct and not in a straight line.
//
// Example:
// Input: points = [[1,1],[2,3],[3,2]]
// Output: true
//
// Constraints:
// points.length == 3
// 	points[i].length == 2
// 	0 <= xi, yi <= 100
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isBoomerang(int** points, int pointsSize, int* pointsColSize) {
    // Check if the points are distinct
    if (pointsSize != 3) {
        return false; // Not enough points to form a boomerang
    }
    
    // Check if any two points are the same
    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                return false; // Found two identical points
            }
        }
    }
    
    // Check if the points are in a straight line
    int x1 = points[0][0], y1 = points[0][1];
    int x2 = points[1][0], y2 = points[1][1];
    int x3 = points[2][0], y3 = points[2][1];
    
    // Calculate the area of the triangle formed by the three points
    int area = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    
    return area != 0; // If area is zero, the points are collinear      
}
