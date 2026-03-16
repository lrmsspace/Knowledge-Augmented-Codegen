// Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
//
// Return the minimum possible sum of the area of these rectangles.
//
// Note that the rectangles are allowed to touch.
//
// Example:
// Input: grid = [[1,0,1],[1,1,1]]
//
// Output: 5
//
// Explanation:
//
//
//
//
// 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
// 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
// 	The 1 at (1, 1) is covered by a rectangle of area 1.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 30
// 	grid[i][j] is either 0 or 1.
// 	The input is generated such that there are at least three 1's in grid.
//

int minimumSum(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize, cols = gridColSize[0];
    int left[rows], right[rows], top[cols], bottom[cols];
    memset(left, -1, sizeof(left));
    memset(right, -1, sizeof(right));
    memset(top, -1, sizeof(top));
    memset(bottom, -1, sizeof(bottom));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 1) {
                if (left[r] == -1) left[r] = c;
                right[r] = c;
                if (top[c] == -1) top[c] = r;
                bottom[c] = r;
            }
        }
    }

    int minArea = __INT_MAX__;
    for (int c1 = 0; c1 < cols; ++c1) {
        for (int c2 = c1; c2 < cols; ++c2) {
            for (int c3 = c2; c3 < cols; ++c3) {
                int area = 0;
                for (int r = 0; r < rows; ++r) {
                    if (left[r] != -1) {
                        if (left[r] >= c1 && right[r] <= c1) {
                            area += (right[r] - left[r] + 1);
                        } else if (left[r] >= c2 && right[r] <= c2) {
                            area += (right[r] - left[r] + 1);
                        } else if (left[r] >= c3 && right[r] <= c3) {
                            area += (right[r] - left[r] + 1);
                        } else {
                            area = __INT_MAX__;
                            break;
                        }
                    }
                }
                if (area < minArea) {
                    minArea = area;
                }
            }
        }
    }

    return minArea;     
}
