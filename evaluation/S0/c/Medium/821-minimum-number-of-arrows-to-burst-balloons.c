// Source: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/   |   Difficulty: Medium
//
// Problem Description:
// There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.
//
// Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.
//
// Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
//
// Example:
// Input: points = [[10,16],[2,8],[1,6],[7,12]]
// Output: 2
// Explanation: The balloons can be burst by 2 arrows:
// - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
// - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
//
// Constraints:
// 1 <= points.length <= 105
// 	points[i].length == 2
// 	-231 <= xstart < xend <= 231 - 1
//

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize) {
     
    if (pointsSize == 0) return 0;
    
    // Sort the points based on their end coordinate
    int compare(const void* a, const void* b) {
        int* pointA = *(int**)a;
        int* pointB = *(int**)b;
        return pointA[1] - pointB[1];
    }
    qsort(points, pointsSize, sizeof(int*), compare);

    int arrows = 1;
    int currentEnd = points[0][1];

    for (int i = 1; i < pointsSize; i++) {
        if (points[i][0] > currentEnd) {
            arrows++;
            currentEnd = points[i][1];
        }
    }

    return arrows;
}