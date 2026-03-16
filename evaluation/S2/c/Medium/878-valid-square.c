// Source: https://leetcode.com/problems/valid-square/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.
//
// The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.
//
// A valid square has four equal sides with positive length and four equal angles (90-degree angles).
//
// Example:
// Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
// Output: true
//
// Constraints:
// p1.length == p2.length == p3.length == p4.length == 2
// 	-104 <= xi, yi <= 104
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

bool validSquare(int* p1, int p1Size, int* p2, int p2Size, int* p3, int p3Size, int* p4, int p4Size) {
    // Helper function to calculate the squared distance between two points
    int distanceSquared(int* a, int* b) {
        return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
    }

    // Store the points in an array for easier access
    int* points[4] = {p1, p2, p3, p4};

    // Calculate the distances between all pairs of points
    int distances[6];
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            distances[index++] = distanceSquared(points[i], points[j]);
        }
    }

    // Sort the distances
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            if (distances[j] > distances[j + 1]) {
                int temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
            }
        }
    }

    // Check the conditions for a valid square
    return (distances[0] > 0 && 
            distances[0] == distances[1] && 
            distances[0] == distances[2] && 
            distances[0] == distances[3] && 
            distances[4] == distances[5] && 
            distances[4] == 2 * distances[0]);      
}
