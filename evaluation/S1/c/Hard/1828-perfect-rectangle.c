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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isRectangleCover(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    long long area = 0;
    int minX = 100000, minY = 100000, maxX = -100000, maxY = -100000;
    typedef struct Point {
        int x;
        int y;
        struct Point* next;
    } Point;
    #define HASH_SIZE 20011
    Point* hashMap[HASH_SIZE] = {0};

    for (int i = 0; i < rectanglesSize; i++) {
        int x1 = rectangles[i][0], y1 = rectangles[i][1];
        int x2 = rectangles[i][2], y2 = rectangles[i][3];
        area += (long long)(x2 - x1) * (y2 - y1);
        if (x1 < minX) minX = x1;
        if (y1 < minY) minY = y1;
        if (x2 > maxX) maxX = x2;
        if (y2 > maxY) maxY = y2;

        int points[4][2] = {{x1,y1}, {x1,y2}, {x2,y1}, {x2,y2}};
        for (int j = 0; j < 4; j++) {
            int hx = (points[j][0] + 100000) % HASH_SIZE;
            int hy = (points[j][1] + 100000) % HASH_SIZE;
            int h = (hx * 31 + hy) % HASH_SIZE;
            Point* p = hashMap[h];
            Point* prev = NULL;
            while (p) {
                if (p->x == points[j][0] && p->y == points[j][1]) break;
                prev = p; p = p->next;
            }
            if (p) {
                /* point exists, remove it */
                if (prev) prev->next = p->next;
                else hashMap[h] = p->next;
                free(p);
            } else {
                /* add new point */
                Point* np = (Point*)malloc(sizeof(Point));
                if (!np) return false; /* allocation failure, but continue gracefully */
                np->x = points[j][0]; np->y = points[j][1];
                np->next = hashMap[h];
                hashMap[h] = np;
            }
        }    
    }
    long long expectedArea = (long long)(maxX - minX) * (maxY - minY);
    if (area != expectedArea) return false;
    int cornerCount = 0;    
    for (int h = 0; h < HASH_SIZE; h++) {
        Point* p = hashMap[h];
        while (p) {
            if ((p->x == minX && p->y == minY) ||
                (p->x == minX && p->y == maxY) ||
                (p->x == maxX && p->y == minY) ||
                (p->x == maxX && p->y == maxY)) {
                cornerCount++;
            } else {
                return false;
            }
            Point* temp = p;
            p = p->next;
            free(temp);
        }
    }
    return cornerCount == 4;   
}
