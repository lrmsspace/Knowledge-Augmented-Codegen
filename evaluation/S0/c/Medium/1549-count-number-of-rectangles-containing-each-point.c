// Source: https://leetcode.com/problems/count-number-of-rectangles-containing-each-point/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array rectangles where rectangles[i] = [li, hi] indicates that ith rectangle has a length of li and a height of hi. You are also given a 2D integer array points where points[j] = [xj, yj] is a point with coordinates (xj, yj).
//
// The ith rectangle has its bottom-left corner point at the coordinates (0, 0) and its top-right corner point at (li, hi).
//
// Return an integer array count of length points.length where count[j] is the number of rectangles that contain the jth point.
//
// The ith rectangle contains the jth point if 0 <= xj <= li and 0 <= yj <= hi. Note that points that lie on the edges of a rectangle are also considered to be contained by that rectangle.
//
// Example:
// Input: rectangles = [[1,2],[2,3],[2,5]], points = [[2,1],[1,4]]
// Output: [2,1]
// Explanation: 
// The first rectangle contains no points.
// The second rectangle contains only the point (2, 1).
// The third rectangle contains the points (2, 1) and (1, 4).
// The number of rectangles that contain the point (2, 1) is 2.
// The number of rectangles that contain the point (1, 4) is 1.
// Therefore, we return [2, 1].
//
// Constraints:
// 1 <= rectangles.length, points.length <= 5 * 104
// 	rectangles[i].length == points[j].length == 2
// 	1 <= li, xj <= 109
// 	1 <= hi, yj <= 100
// 	All the rectangles are unique.
// 	All the points are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countRectangles(int** rectangles, int rectanglesSize, int* rectanglesColSize, int** points, int pointsSize, int* pointsColSize, int* returnSize) {
    int maxHeight = 100;
    int* heightCount = (int*)calloc(maxHeight + 1, sizeof(int));
    for (int i = 0; i < rectanglesSize; i++) {
        int height = rectangles[i][1];
        heightCount[height]++;
    }
    
    // Create a suffix sum array to count rectangles with height >= h
    for (int h = maxHeight - 1; h >= 1; h--) {
        heightCount[h] += heightCount[h + 1];
    }
    
    int* result = (int*)malloc(pointsSize * sizeof(int));
    for (int i = 0; i < pointsSize; i++) {
        int x = points[i][0];
        int y = points[i][1];
        
        // Count rectangles that can contain the point
        int count = 0;
        for (int h = y; h <= maxHeight; h++) {
            count += heightCount[h];
        }
        
        // Filter by length
        for (int j = 0; j < rectanglesSize; j++) {
            if (rectangles[j][1] >= y && rectangles[j][0] < x) {
                count--;
            }
        }
        
        result[i] = count;
    }
    
    *returnSize = pointsSize;
    free(heightCount);
    return result;      
}
