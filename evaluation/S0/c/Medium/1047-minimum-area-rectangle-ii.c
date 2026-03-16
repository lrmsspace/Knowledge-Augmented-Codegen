// Source: https://leetcode.com/problems/minimum-area-rectangle-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
//
// Return the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the X and Y axes. If there is not any such rectangle, return 0.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: points = [[1,2],[2,1],[1,0],[0,1]]
// Output: 2.00000
// Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
//
// Constraints:
// 1 <= points.length <= 50
// 	points[i].length == 2
// 	0 <= xi, yi <= 4 * 104
// 	All the given points are unique.
//

double minAreaFreeRect(int** points, int pointsSize, int* pointsColSize) {
    #define MAX_POINTS 50
    #define HASH_SIZE 100003

    typedef struct Point {
        int x;
        int y;
        struct Point* next;
    } Point;

    Point* hashTable[HASH_SIZE] = {0};

    unsigned int hash(int x, int y) {
        return ((unsigned int)(x * 40001 + y)) % HASH_SIZE;
    }

    void insertPoint(int x, int y) {
        unsigned int h = hash(x, y);
        Point* newPoint = (Point*)malloc(sizeof(Point));
        newPoint->x = x;
        newPoint->y = y;
        newPoint->next = hashTable[h];
        hashTable[h] = newPoint;
    }

    int pointExists(int x, int y) {
        unsigned int h = hash(x, y);
        Point* curr = hashTable[h];
        while (curr) {
            if (curr->x == x && curr->y == y) {
                return 1;
            }
            curr = curr->next;
        }
        return 0;
    }

    for (int i = 0; i < pointsSize; i++) {
        insertPoint(points[i][0], points[i][1]);
    }

    double minArea = __DBL_MAX__;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = 0; j < pointsSize; j++) {
            if (i == j) continue;
            for (int k = 0; k < pointsSize; k++) {
                if (k == i || k == j) continue;

                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                int x3 = points[k][0], y3 = points[k][1];

                int vx1 = x2 - x1;
                int vy1 = y2 - y1;
                int vx2 = x3 - x1;
                int vy2 = y3 - y1;

                if (vx1 * vx2 + vy1 * vy2 != 0) continue;

                int x4 = x3 + vx1;
                int y4 = y3 + vy1;

                if (pointExists(x4, y4)) {
                    double area = sqrt((double)(vx1 * vx1 + vy1 * vy1)) * sqrt((double)(vx2 * vx2 + vy2 * vy2));
                    if (area < minArea) {
                        minArea = area;
                    }
                }
            }
        }
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        Point* curr = hashTable[i];
        while (curr) {
            Point* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    return (minArea == __DBL_MAX__) ? 0.0 : minArea;
}
