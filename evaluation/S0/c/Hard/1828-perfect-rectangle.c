// Source: https://leetcode.com/problems/perfect-rectangle/   |   Difficulty: Hard
//
// Problem Description:
// Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
//
// Return true if all the rectangles together form an exact cover of a rectangular region.
//
// Example:
// Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
// Output: true
// Explanation: All 5 rectangles together form an exact cover of a rectangular region.
//
// Constraints:
// 1 <= rectangles.length <= 2 * 104
// 	rectangles[i].length == 4
// 	-105 <= xi < ai <= 105
// 	-105 <= yi < bi <= 105
//

bool isRectangleCover(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    if (rectanglesSize <= 0 || !rectanglesColSize) return false;

    int minX = 100000, minY = 100000, maxX = -100000, maxY = -100000;
    long long areaSum = 0;
    #define HASH_SIZE 100003
    typedef struct Point {
        int x, y;
        struct Point* next;
    } Point;
    Point* hash[HASH_SIZE];
    memset(hash, 0, sizeof(hash));

    for (int i = 0; i < rectanglesSize; ++i) {
        int x1 = rectangles[i][0], y1 = rectangles[i][1];
        int x2 = rectangles[i][2], y2 = rectangles[i][3];

        minX = (x1 < minX) ? x1 : minX;
        minY = (y1 < minY) ? y1 : minY;
        maxX = (x2 > maxX) ? x2 : maxX;
        maxY = (y2 > maxY) ? y2 : maxY;

        areaSum += (long long)(x2 - x1) * (y2 - y1);

        int points[4][2] = {{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}};
        for (int j = 0; j < 4; ++j) {
            int px = points[j][0];
            int py = points[j][1];
            int hashKey = ((px + 100000) * 200001 + (py + 100000)) % HASH_SIZE;
            Point* curr = hash[hashKey];
            Point* prev = NULL;
            int found = 0;
            while (curr) {
                if (curr->x == px && curr->y == py) {
                    found = 1;
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
            if (found) {
                // Remove point
                if (prev) {
                    prev->next = curr->next;
                } else {
                    hash[hashKey] = curr->next;
                }
                free(curr);
            } else {
                // Add point
                Point* newPoint = (Point*)malloc(sizeof(Point));
                newPoint->x = px;
                newPoint->y = py;
                newPoint->next = hash[hashKey];
                hash[hashKey] = newPoint;
            }
        }

}
    long long expectedArea = (long long)(maxX - minX) * (maxY - minY);
    if (areaSum != expectedArea) return false;

    int cornerCount = 0;
    int corners[4][2] = {{minX, minY}, {minX, maxY}, {maxX, minY}, {maxX, maxY}};
    for (int i = 0; i < 4; ++i) {
        int px = corners[i][0];
        int py = corners[i][1];
        int hashKey = ((px + 100000) * 200001 + (py + 100000)) % HASH_SIZE;
        Point* curr = hash[hashKey];
        int found = 0;
        while (curr) {
            if (curr->x == px && curr->y == py) {
                found = 1;
                break;
            }
            curr = curr->next;
        }
        if (found) {
            cornerCount++;
            // Remove corner point
            Point* toDelete = hash[hashKey];
            Point* prev = NULL;
            while (toDelete) {
                if (toDelete->x == px && toDelete->y == py) {
                    if (prev) {
                        prev->next = toDelete->next;
                    } else {
                        hash[hashKey] = toDelete->next;
                    }
                    free(toDelete);
                    break;
                }
                prev = toDelete;
                toDelete = toDelete->next;
            }
        }
    }

    // Check remaining points in hash
    for (int i = 0; i < HASH_SIZE; ++i) {
        Point* curr = hash[i];
        while (curr) {
            cornerCount++;
            Point* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return cornerCount == 4;
}