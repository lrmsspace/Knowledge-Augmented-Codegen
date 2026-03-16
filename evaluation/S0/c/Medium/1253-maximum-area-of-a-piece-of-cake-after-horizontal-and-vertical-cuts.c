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

int maxArea(int h, int w, int* horizontalCuts, int horizontalCutsSize, int* verticalCuts, int verticalCutsSize) {
    #define MOD 1000000007
    // Helper function to compare two integers (used for qsort)
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }

    // Sort the horizontal and vertical cuts
    qsort(horizontalCuts, horizontalCutsSize, sizeof(int), compare);
    qsort(verticalCuts, verticalCutsSize, sizeof(int), compare);

    // Find maximum height between horizontal cuts
    long maxHeight = horizontalCuts[0]; // Distance from top to first cut
    for (int i = 1; i < horizontalCutsSize; i++) {
        long height = horizontalCuts[i] - horizontalCuts[i - 1];
        if (height > maxHeight) {
            maxHeight = height;
        }
    }
    // Check distance from last cut to bottom
    long lastHeight = h - horizontalCuts[horizontalCutsSize - 1];
    if (lastHeight > maxHeight) {
        maxHeight = lastHeight;
    }

    // Find maximum width between vertical cuts
    long maxWidth = verticalCuts[0]; // Distance from left to first cut
    for (int i = 1; i < verticalCutsSize; i++) {
        long width = verticalCuts[i] - verticalCuts[i - 1];
        if (width > maxWidth) {
            maxWidth = width;
        }
    }
    // Check distance from last cut to right edge
    long lastWidth = w - verticalCuts[verticalCutsSize - 1];
    if (lastWidth > maxWidth) {
        maxWidth = lastWidth;
    }

    // Calculate maximum area modulo MOD
    return (int)((maxHeight * maxWidth) % MOD);     
}
