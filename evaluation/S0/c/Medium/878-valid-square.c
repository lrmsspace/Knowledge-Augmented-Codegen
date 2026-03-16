// Source: https://leetcode.com/problems/valid-square/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.
//
// The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.
//
// A valid square has four equal sides with positive length and four equal angles (90-degree angles).
//
// Example:
// Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
// Output: true
//
// Constraints:
// p1.length == p2.length == p3.length == p4.length == 2
// 	-104 <= xi, yi <= 104
//

bool validSquare(int* p1, int p1Size, int* p2, int p2Size, int* p3, int p3Size, int* p4, int p4Size) {
    int points[4][2] = { {p1[0], p1[1]}, {p2[0], p2[1]}, {p3[0], p3[1]}, {p4[0], p4[1]} };
    int dists[6];
    int idx = 0;

    // Calculate all pairwise squared distances
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            int dx = points[i][0] - points[j][0];
            int dy = points[i][1] - points[j][1];
            dists[idx++] = dx * dx + dy * dy;
        }
    }

    // Sort the distances
    for (int i = 0; i < 6 - 1; i++) {
        for (int j = 0; j < 6 - i - 1; j++) {
            if (dists[j] > dists[j + 1]) {
                int temp = dists[j];
                dists[j] = dists[j + 1];
                dists[j + 1] = temp;
            }
        }
    }

    // Check the conditions for a valid square
    // The first 4 distances should be equal (sides) and greater than 0
    // The last 2 distances should be equal (diagonals) and equal to side
    return dists[0] > 0 &&
           dists[0] == dists[1] &&
           dists[1] == dists[2] &&
           dists[2] == dists[3] &&
           dists[4] == dists[5] &&
           dists[4] == 2 * dists[0];
}
