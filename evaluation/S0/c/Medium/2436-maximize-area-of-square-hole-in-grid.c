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

int maximizeSquareHoleArea(int n, int m, int* hBars, int hBarsSize, int* vBars, int vBarsSize) {
    // Helper function to find the maximum gap in a sorted array
    int findMaxGap(int* bars, int size, int limit) {
        // Sort the bars
        qsort(bars, size, sizeof(int), (int (*)(const void*, const void*))strcmp);
        
        int maxGap = 0;
        int prev = 1; // Start from the first bar at position 1
        
        for (int i = 0; i < size; i++) {
            int gap = bars[i] - prev;
            if (gap > maxGap) {
                maxGap = gap;
            }
            prev = bars[i];
        }
        
        // Check the gap between the last bar and the limit + 1
        int finalGap = (limit + 2) - prev;
        if (finalGap > maxGap) {
            maxGap = finalGap;
        }
        
        return maxGap;
    }

    // Find maximum gaps in horizontal and vertical bars
    int maxHGap = findMaxGap(hBars, hBarsSize, n);
    int maxVGap = findMaxGap(vBars, vBarsSize, m);
    
    // The area of the largest square hole is the square of the minimum of the two maximum gaps
    int sideLength = (maxHGap < maxVGap) ? maxHGap : maxVGap;
    return sideLength * sideLength;     
}
