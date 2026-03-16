// Source: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
//
// Count the number of pairs of points (A, B), where
//
//
// 	A is on the upper left side of B, and
// 	there are no other points in the rectangle (or line) they make (including the border), except for the points A and B.
//
//
// Return the count.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
//
// Output: 0
//
// Explanation:
//
//
//
// There is no way to choose A and B such that A is on the upper left side of B.
//
// Constraints:
// 2 <= n <= 50
// 	points[i].length == 2
// 	0 <= points[i][0], points[i][1] <= 50
// 	All points[i] are distinct.
//

int numberOfPairs(int** points, int pointsSize, int* pointsColSize) {
    int count = 0;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = 0; j < pointsSize; j++) {
            if (points[i][0] < points[j][0] && points[i][1] > points[j][1]) {
                int valid = 1;
                for (int k = 0; k < pointsSize; k++) {
                    if (k != i && k != j) {
                        if (points[k][0] >= points[i][0] && points[k][0] <= points[j][0] &&
                            points[k][1] <= points[i][1] && points[k][1] >= points[j][1]) {
                            valid = 0;
                            break;
                        }
                    }
                }
                if (valid) {
                    count++;
                }
            }
        }
    }
    return count;       
}
