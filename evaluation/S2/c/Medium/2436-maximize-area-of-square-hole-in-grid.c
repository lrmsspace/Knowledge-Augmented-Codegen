// Source: https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given the two integers, n and m and two integer arrays, hBars and vBars. The grid has n + 2 horizontal and m + 2 vertical bars, creating 1 x 1 unit cells. The bars are indexed starting from 1.
//
// You can remove some of the bars in hBars from horizontal bars and some of the bars in vBars from vertical bars. Note that other bars are fixed and cannot be removed.
//
// Return an integer denoting the maximum area of a square-shaped hole in the grid, after removing some bars (possibly none).
//
// Example:
// Input: n = 2, m = 1, hBars = [2,3], vBars = [2]
//
// Output: 4
//
// Explanation:
//
// The left image shows the initial grid formed by the bars. The horizontal bars are [1,2,3,4], and the vertical bars are [1,2,3].
//
// One way to get the maximum square-shaped hole is by removing horizontal bar 2 and vertical bar 2.
//
// Constraints:
// 1 <= n <= 109
// 	1 <= m <= 109
// 	1 <= hBars.length <= 100
// 	2 <= hBars[i] <= n + 1
// 	1 <= vBars.length <= 100
// 	2 <= vBars[i] <= m + 1
// 	All values in hBars are distinct.
// 	All values in vBars are distinct.
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

int maximizeSquareHoleArea(int n, int m, int* hBars, int hBarsSize, int* vBars, int vBarsSize) {
    int maxHGap = 0, maxVGap = 0;

    // Calculate maximum gap between horizontal bars
    for (int i = 0; i < hBarsSize; i++) {
        int prevBar = (i == 0) ? 1 : hBars[i - 1];
        int nextBar = (i == hBarsSize - 1) ? n + 2 : hBars[i + 1];
        int gap = nextBar - prevBar - 1;
        if (gap > maxHGap) {
            maxHGap = gap;
        }
    }

    // Calculate maximum gap between vertical bars
    for (int i = 0; i < vBarsSize; i++) {
        int prevBar = (i == 0) ? 1 : vBars[i - 1];
        int nextBar = (i == vBarsSize - 1) ? m + 2 : vBars[i + 1];
        int gap = nextBar - prevBar - 1;
        if (gap > maxVGap) {
            maxVGap = gap;
        }
    }

    // The area of the largest square hole is the minimum of the two maximum gaps
    int maxSquareSide = (maxHGap < maxVGap) ? maxHGap : maxVGap;
    return maxSquareSide * maxSquareSide;       
}
