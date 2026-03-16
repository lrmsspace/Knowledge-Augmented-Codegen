// Source: https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers xCorner and yCorner, and a 2D array circles, where circles[i] = [xi, yi, ri] denotes a circle with center at (xi, yi) and radius ri.
//
// There is a rectangle in the coordinate plane with its bottom left corner at the origin and top right corner at the coordinate (xCorner, yCorner). You need to check whether there is a path from the bottom left corner to the top right corner such that the entire path lies inside the rectangle, does not touch or lie inside any circle, and touches the rectangle only at the two corners.
//
// Return true if such a path exists, and false otherwise.
//
// Example:
// Input: xCorner = 3, yCorner = 4, circles = [[2,1,1]]
//
// Output: true
//
// Explanation:
//
//
//
// The black curve shows a possible path between (0, 0) and (3, 4).
//
// Constraints:
// 3 <= xCorner, yCorner <= 109
// 	1 <= circles.length <= 1000
// 	circles[i].length == 3
// 	1 <= xi, yi, ri <= 109
//

bool canReachCorner(int xCorner, int yCorner, int** circles, int circlesSize, int* circlesColSize) {
    typedef struct {
        long long x;
        long long y;
        long long r;
    } Circle;

    Circle* circleList = (Circle*)malloc(circlesSize * sizeof(Circle));
    for (int i = 0; i < circlesSize; ++i) {
        circleList[i].x = circles[i][0];
        circleList[i].y = circles[i][1];
        circleList[i].r = circles[i][2];
    }

    int isBlocked(long long x, long long y) {
        for (int i = 0; i < circlesSize; ++i) {
            long long dx = x - circleList[i].x;
            long long dy = y - circleList[i].y;
            if (dx * dx + dy * dy <= circleList[i].r * circleList[i].r) {
                return 1;
            }
        }
        return 0;
    }

    if (isBlocked(0, 0) || isBlocked(xCorner, yCorner)) {
        free(circleList);
        return false;
    }

    free(circleList);
    return true;
}
