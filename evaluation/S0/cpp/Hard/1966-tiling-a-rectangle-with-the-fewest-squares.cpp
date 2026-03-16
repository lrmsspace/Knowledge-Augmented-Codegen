// Source: https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/   |   Difficulty: Hard
//
// Problem Description:
// Given a rectangle of size n x m, return the minimum number of integer-sided squares that tile the rectangle.
//
// Example:
// Input: n = 2, m = 3
// Output: 3
// Explanation: 3 squares are necessary to cover the rectangle.
// 2 (squares of 1x1)
// 1 (square of 2x2)
//
// Constraints:
// 1 <= n, m <= 13
//

class Solution {
public:
    int tilingRectangle(int n, int m) {
        vector<int> heights(m, 0);
        int result = INT_MAX;

        function<void(int, int)> backtrack = [&](int placedSquares, int filledCells) {
            if (filledCells == n * m) {
                result = min(result, placedSquares);
                return;
            }
            if (placedSquares >= result) return;

            int col = 0;
            while (col < m && heights[col] == n) col++;
            if (col == m) return;

            int row = heights[col];
            int maxSize = 1;
            while (col + maxSize <= m && all_of(heights.begin() + col, heights.begin() + col + maxSize, [&](int h) { return h == row; }) && row + maxSize <= n) {
                maxSize++;
            }
            maxSize--;

            for (int size = maxSize; size >= 1; size--) {
                for (int k = 0; k < size; k++) {
                    heights[col + k] += size;
                }
                backtrack(placedSquares + 1, filledCells + size * size);
                for (int k = 0; k < size; k++) {
                    heights[col + k] -= size;
                }
            }
        };

        backtrack(0, 0);
        return result;          
    }
};
