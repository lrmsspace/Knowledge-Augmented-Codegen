// Source: https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/   |   Difficulty: Medium
//
// Problem Description:
// You are given a rectangular cake of size h x w and two arrays of integers horizontalCuts and verticalCuts where:
//
//
// 	horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal cut and similarly, and
// 	verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
//
//
// Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the arrays horizontalCuts and verticalCuts. Since the answer can be a large number, return this modulo 109 + 7.
//
// Example:
// Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
// Output: 4 
// Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts. After you cut the cake, the green piece of cake has the maximum area.
//
// Constraints:
// 2 <= h, w <= 109
// 	1 <= horizontalCuts.length <= min(h - 1, 105)
// 	1 <= verticalCuts.length <= min(w - 1, 105)
// 	1 <= horizontalCuts[i] < h
// 	1 <= verticalCuts[i] < w
// 	All the elements in horizontalCuts are distinct.
// 	All the elements in verticalCuts are distinct.
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

int maxArea(int h, int w, int* horizontalCuts, int horizontalCutsSize, int* verticalCuts, int verticalCutsSize) {
    // Sort the horizontal and vertical cuts
    qsort(horizontalCuts, horizontalCutsSize, sizeof(int), cmp);
    qsort(verticalCuts, verticalCutsSize, sizeof(int), cmp);

    // Calculate the maximum horizontal gap
    int maxHorizontalGap = horizontalCuts[0]; // Distance from top to first cut
    for (int i = 1; i < horizontalCutsSize; i++) {
        int gap = horizontalCuts[i] - horizontalCuts[i - 1];
        if (gap > maxHorizontalGap) {
            maxHorizontalGap = gap;
        }
    }
    // Distance from last cut to bottom
    int lastHorizontalGap = h - horizontalCuts[horizontalCutsSize - 1];
    if (lastHorizontalGap > maxHorizontalGap) {
        maxHorizontalGap = lastHorizontalGap;
    }

    // Calculate the maximum vertical gap
    int maxVerticalGap = verticalCuts[0]; // Distance from left to first cut
    for (int i = 1; i < verticalCutsSize; i++) {
        int gap = verticalCuts[i] - verticalCuts[i - 1];
        if (gap > maxVerticalGap) {
            maxVerticalGap = gap;
        }
    }
    // Distance from last cut to right
    int lastVerticalGap = w - verticalCuts[verticalCutsSize - 1];
    if (lastVerticalGap > maxVerticalGap) {
        maxVerticalGap = lastVerticalGap;
    }

    // Calculate the area and return it modulo 10^9 + 7
    long long area = (long long)maxHorizontalGap * maxVerticalGap;
    return area % 1000000007;       
}
