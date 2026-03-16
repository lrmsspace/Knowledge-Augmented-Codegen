// Source: https://leetcode.com/problems/maximum-number-of-visible-points/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points, an integer angle, and your location, where location = [posx, posy] and points[i] = [xi, yi] both denote integral coordinates on the X-Y plane.
//
// Initially, you are facing directly east from your position. You cannot move from your position, but you can rotate. In other words, posx and posy cannot be changed. Your field of view in degrees is represented by angle, determining how wide you can see from any given view direction. Let d be the amount in degrees that you rotate counterclockwise. Then, your field of view is the inclusive range of angles [d - angle/2, d + angle/2].
//
//
// Your browser does not support the video tag or this video format.
//
//
// You can see some set of points if, for each point, the angle formed by the point, your position, and the immediate east direction from your position is in your field of view.
//
// There can be multiple points at one coordinate. There may be points at your location, and you can always see these points regardless of your rotation. Points do not obstruct your vision to other points.
//
// Return the maximum number of points you can see.
//
// Example:
// Input: points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
// Output: 3
// Explanation: The shaded region represents your field of view. All points can be made visible in your field of view, including [3,3] even though [2,2] is in front and in the same line of sight.
//
// Constraints:
// 1 <= points.length <= 105
// 	points[i].length == 2
// 	location.length == 2
// 	0 <= angle < 360
// 	0 <= posx, posy, xi, yi <= 100
//

int visiblePoints(int** points, int pointsSize, int* pointsColSize, int angle, int* location, int locationSize) {
    double *angles = (double*)malloc(sizeof(double) * pointsSize * 2);
    if (!angles) return 0;
    int samePosCount = 0;
    int angCount = 0;
    int locX = location[0], locY = location[1];

    for (int i = 0; i < pointsSize; ++i) {
        int x = points[i][0], y = points[i][1];
        if (x == locX && y == locY) {
            samePosCount++;
        } else {
            double ang = atan2((double)(y - locY), (double)(x - locX)) * 180.0 / 3.14159265358979323846;
            if (ang < 0) ang += 360.0;
            angles[angCount++] = ang;
        }
    }

    qsort(angles, angCount, sizeof(double), cmpInt);

    /* duplicate angles with +360 for circular wrap-around */
    for (int i = 0; i < angCount; ++i) {
        angles[angCount + i] = angles[i] + 360.0;
    }
    int totalAngCount = angCount * 2;

    int maxVisible = 0;
    int right = 0;
    for (int left = 0; left < angCount; ++left) {
        while (right < totalAngCount && angles[right] - angles[left] <= angle) {
            right++;
        }
        int visibleNow = right - left;
        if (visibleNow > maxVisible) {
            maxVisible = visibleNow;
        }
    }

    free(angles);
    return maxVisible + samePosCount;       
}
