// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n points on an infinite plane. You are given two integer arrays xCoord and yCoord where (xCoord[i], yCoord[i]) represents the coordinates of the ith point.
//
// Your task is to find the maximum area of a rectangle that:
//
//
// 	Can be formed using four of these points as its corners.
// 	Does not contain any other point inside or on its border.
// 	Has its edges parallel to the axes.
//
//
// Return the maximum area that you can obtain or -1 if no such rectangle is possible.
//
// Example:
// Input: xCoord = [1,1,3,3], yCoord = [1,3,1,3]
//
// Output: 4
//
// Explanation:
//
//
//
// We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
//
// Constraints:
// 1 <= xCoord.length == yCoord.length <= 2 * 105
// 	0 <= xCoord[i], yCoord[i] <= 8 * 107
// 	All the given points are unique.
//

long long maxRectangleArea(int* xCoord, int xCoordSize, int* yCoord, int yCoordSize) {
    typedef struct Point {
        int x;
        int y;
    } Point;

    int n = xCoordSize;
    Point* points = (Point*)malloc(n * sizeof(Point));
    for (int i = 0; i < n; ++i) {
        points[i].x = xCoord[i];
        points[i].y = yCoord[i];
    }

    // Sort points by x, then by y
    int compare(const void* a, const void* b) {
        Point* p1 = (Point*)a;
        Point* p2 = (Point*)b;
        if (p1->x != p2->x) return p1->x - p2->x;
        return p1->y - p2->y;
    }
    qsort(points, n, sizeof(Point), compare);

    // Use a hash set to store points for O(1) lookup
    #define TABLE_SIZE 262144
    typedef struct HashEntry {
        int x;
        int y;
        struct HashEntry* next;
    } HashEntry;

    HashEntry** table = (HashEntry**)calloc(TABLE_SIZE, sizeof(HashEntry*));
    for (int i = 0; i < n; ++i) {
        int h = (unsigned int)(points[i].x * 31 + points[i].y) % TABLE_SIZE;
        HashEntry* entry = (HashEntry*)malloc(sizeof(HashEntry));
        entry->x = points[i].x;
        entry->y = points[i].y;
        entry->next = table[h];
        table[h] = entry;
    }

    long long maxArea = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (points[i].x == points[j].x || points[i].y == points[j].y) continue;

            // Check if the other two corners exist
            int x1 = points[i].x, y1 = points[i].y;
            int x2 = points[j].x, y2 = points[j].y;

            int h1 = (unsigned int)(x1 * 31 + y2) % TABLE_SIZE;
            int h2 = (unsigned int)(x2 * 31 + y1) % TABLE_SIZE;
            HashEntry* entry1 = table[h1];
            HashEntry* entry2 = table[h2];
            bool found1 = false, found2 = false;
            while (entry1) {
                if (entry1->x == x1 && entry1->y == y2) {
                    found1 = true;
                    break;
                }
                entry1 = entry1->next;
            }
            while (entry2) {
                if (entry2->x == x2 && entry2->y == y1) {
                    found2 = true;
                    break;
                }
                entry2 = entry2->next;
            }
            if (found1 && found2) {
                long long area = (long long)abs(x2 - x1) * abs(y2 - y1);
                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }
    // Free hash table
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashEntry* entry = table[i];
        while (entry) {
            HashEntry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(table);
    free(points);
    return maxArea;
}
