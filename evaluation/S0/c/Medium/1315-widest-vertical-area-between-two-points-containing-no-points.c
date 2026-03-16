// Source: https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/   |   Difficulty: Medium
//
// Problem Description:
// Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between two points such that no points are inside the area.
//
// A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite height). The widest vertical area is the one with the maximum width.
//
// Note that points on the edge of a vertical area are not considered included in the area.
//
// Example:
// ​
//
// Input: points = [[8,7],[9,9],[7,4],[9,7]]
// Output: 1
// Explanation: Both the red and the blue area are optimal.
//
// Constraints:
// n == points.length
// 	2 <= n <= 105
// 	points[i].length == 2
// 	0 <= xi, yi <= 109
//

int maxWidthOfVerticalArea(int** points, int pointsSize, int* pointsColSize) {
    int* x_coords = (int*)malloc(pointsSize * sizeof(int));
    for (int i = 0; i < pointsSize; i++) {
        x_coords[i] = points[i][0];
    }

    // Sort the x-coordinates
    qsort(x_coords, pointsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int max_width = 0;
    for (int i = 1; i < pointsSize; i++) {
        int width = x_coords[i] - x_coords[i - 1];
        if (width > max_width) {
            max_width = width;
        }
    }

    free(x_coords);
    return max_width;       
}
