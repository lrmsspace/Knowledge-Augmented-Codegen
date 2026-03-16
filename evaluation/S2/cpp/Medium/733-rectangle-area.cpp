// Source: https://leetcode.com/problems/rectangle-area/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.
//
// The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).
//
// The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).
//
// Example:
// Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
// Output: 45
//
// Constraints:
// -104 <= ax1 <= ax2 <= 104
// 	-104 <= ay1 <= ay2 <= 104
// 	-104 <= bx1 <= bx2 <= 104
// 	-104 <= by1 <= by2 <= 104
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        // Calculate the area of the first rectangle
        int areaA = (ax2 - ax1) * (ay2 - ay1);
        
        // Calculate the area of the second rectangle
        int areaB = (bx2 - bx1) * (by2 - by1);
        
        // Calculate the overlap area
        int overlapWidth = std::max(0, std::min(ax2, bx2) - std::max(ax1, bx1));
        int overlapHeight = std::max(0, std::min(ay2, by2) - std::max(ay1, by1));
        int overlapArea = overlapWidth * overlapHeight;
        
        // Total area covered by both rectangles
        return areaA + areaB - overlapArea;         
    }
};
