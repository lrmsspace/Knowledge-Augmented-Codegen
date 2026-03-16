// Source: https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/   |   Difficulty: Hard
//
// Problem Description:
// Alice is throwing n darts on a very large wall. You are given an array darts where darts[i] = [xi, yi] is the position of the ith dart that Alice threw on the wall.
//
// Bob knows the positions of the n darts on the wall. He wants to place a dartboard of radius r on the wall so that the maximum number of darts that Alice throws lie on the dartboard.
//
// Given the integer r, return the maximum number of darts that can lie on the dartboard.
//
// Example:
// Input: darts = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
// Output: 4
// Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
//
// Constraints:
// 1 <= darts.length <= 100
// 	darts[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the darts are unique
// 	1 <= r <= 5000
//

int numPoints(int** darts, int dartsSize, int* dartsColSize, int r) {
    if (dartsSize == 0 || r <= 0) return 0;

    int maxCount = 1;
    double r2 = (double)r * r;

    for (int i = 0; i < dartsSize; ++i) {
        for (int j = i + 1; j < dartsSize; ++j) {
            double x1 = darts[i][0], y1 = darts[i][1];
            double x2 = darts[j][0], y2 = darts[j][1];
            double dx = x2 - x1, dy = y2 - y1;
            double d2 = dx * dx + dy * dy;
            if (d2 > 4.0 * r2) continue; // too far apart

            double mx = (x1 + x2) / 2.0;
            double my = (y1 + y2) / 2.0;
            double q = sqrt(r2 - d2 / 4.0);
            double distX = -dy * q / sqrt(d2);
            double distY = dx * q / sqrt(d2);

            double centers[2][2] = {
                {mx + distX, my + distY},
                {mx - distX, my - distY}
            };

            for (int c = 0; c < 2; ++c) {
                double cx = centers[c][0];
                double cy = centers[c][1];
                int count = 0;
                for (int k = 0; k < dartsSize; ++k) {
                    double ddx = darts[k][0] - cx;
                    double ddy = darts[k][1] - cy;
                    if (ddx * ddx + ddy * ddy <= r2 + 1e-9) {
                        count++;
                    }
                }
                if (count > maxCount) {
                    maxCount = count;
                }
            }
        }
    }

    return maxCount;        
}
