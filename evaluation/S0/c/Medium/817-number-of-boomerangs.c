// Source: https://leetcode.com/problems/number-of-boomerangs/   |   Difficulty: Medium
//
// Problem Description:
// You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
//
// Return the number of boomerangs.
//
// Example:
// Input: points = [[0,0],[1,0],[2,0]]
// Output: 2
// Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
//
// Constraints:
// n == points.length
// 	1 <= n <= 500
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//

int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize) {
    int result = 0;
    for (int i = 0; i < pointsSize; i++) {
        int distanceCount[20001] = {0}; // Distance squared can be at most (2*10^4)^2 = 4*10^8, but we use a hash map approach with a fixed size for simplicity.
        for (int j = 0; j < pointsSize; j++) {
            if (i == j) continue;
            int dx = points[i][0] - points[j][0];
            int dy = points[i][1] - points[j][1];
            int distSq = dx * dx + dy * dy;
            distanceCount[distSq]++;
        }
        for (int k = 0; k < 20001; k++) {
            if (distanceCount[k] > 1) {
                result += distanceCount[k] * (distanceCount[k] - 1);
            }
        }
    }
    return result;      
}
