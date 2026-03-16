// Source: https://leetcode.com/problems/k-closest-points-to-origin/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
//
// The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
//
// You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
//
// Example:
// Input: points = [[1,3],[-2,2]], k = 1
// Output: [[-2,2]]
// Explanation:
// The distance between (1, 3) and the origin is sqrt(10).
// The distance between (-2, 2) and the origin is sqrt(8).
// Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
// We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
//
// Constraints:
// 1 <= k <= points.length <= 104
// 	-104 <= xi, yi <= 104
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** kClosest(int** points, int pointsSize, int* pointsColSize, int k, int* returnSize, int** returnColumnSizes) {
    // Allocate memory for the result array
    int** result = (int**)malloc(k * sizeof(int*));
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    *returnSize = k;

    // Create an array to hold distances and their corresponding points
    typedef struct {
        int distance;
        int index;
    } PointDistance;

    PointDistance* distances = (PointDistance*)malloc(pointsSize * sizeof(PointDistance));

    // Calculate squared distances and store them with their indices
    for (int i = 0; i < pointsSize; i++) {
        int x = points[i][0];
        int y = points[i][1];
        distances[i].distance = x * x + y * y; // Squared distance
        distances[i].index = i;
    }

    // Sort the distances array based on the distance
    qsort(distances, pointsSize, sizeof(PointDistance), [](const void* a, const void* b) {
        return ((PointDistance*)a)->distance - ((PointDistance*)b)->distance;
    });

    // Select the first k points based on sorted distances
    for (int i = 0; i < k; i++) {
        int idx = distances[i].index;
        result[i] = (int*)malloc(2 * sizeof(int));
        result[i][0] = points[idx][0];
        result[i][1] = points[idx][1];
        (*returnColumnSizes)[i] = 2;
    }

    // Free the distances array
    free(distances);

    return result;      
}
