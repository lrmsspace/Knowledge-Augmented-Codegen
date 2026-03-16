// Source: https://leetcode.com/problems/falling-squares/   |   Difficulty: Hard
//
// Problem Description:
// There are several squares being dropped onto the X-axis of a 2D plane.
//
// You are given a 2D integer array positions where positions[i] = [lefti, sideLengthi] represents the ith square with a side length of sideLengthi that is dropped with its left edge aligned with X-coordinate lefti.
//
// Each square is dropped one at a time from a height above any landed squares. It then falls downward (negative Y direction) until it either lands on the top side of another square or on the X-axis. A square brushing the left/right side of another square does not count as landing on it. Once it lands, it freezes in place and cannot be moved.
//
// After each square is dropped, you must record the height of the current tallest stack of squares.
//
// Return an integer array ans where ans[i] represents the height described above after dropping the ith square.
//
// Example:
// Input: positions = [[1,2],[2,3],[6,1]]
// Output: [2,5,5]
// Explanation:
// After the first drop, the tallest stack is square 1 with a height of 2.
// After the second drop, the tallest stack is squares 1 and 2 with a height of 5.
// After the third drop, the tallest stack is still squares 1 and 2 with a height of 5.
// Thus, we return an answer of [2, 5, 5].
//
// Constraints:
// 1 <= positions.length <= 1000
// 	1 <= lefti <= 108
// 	1 <= sideLengthi <= 106
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* fallingSquares(int** positions, int positionsSize, int* positionsColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = positionsSize;
    if (positionsSize <= 0) return NULL;

    int *heights = (int*)malloc(positionsSize * sizeof(int));
    if (!heights) return NULL;

    int maxHeight = 0;
    for (int i = 0; i < positionsSize; ++i) {
        int left = positions[i][0];
        int side = positions[i][1];
        int right = left + side;

        int baseHeight = 0;
        for (int j = 0; j < i; ++j) {
            int prevLeft = positions[j][0];
            int prevSide = positions[j][1];
            int prevRight = prevLeft + prevSide;

            if (!(right <= prevLeft || left >= prevRight)) {
                if (heights[j] > baseHeight) {
                    baseHeight = heights[j];
                }
            }
        }

        heights[i] = baseHeight + side;
        if (heights[i] > maxHeight) {
            maxHeight = heights[i];
        }
        heights[i] = maxHeight; /* store the current max height */
    }

    return heights;     
}
