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

/**
 * @param {number[][]} points
 * @param {number} angle
 * @param {number[]} location
 * @return {number}
 */
var visiblePoints = function(points, angle, location) {
    const angles = [];
    let sameLocationCount = 0;
    const [posx, posy] = location;
    for (const [x, y] of points) {
        if (x === posx && y === posy) {
            sameLocationCount++;
        } else {
            const angleToPoint = Math.atan2(y - posy, x - posx) * (180 / Math.PI);
            angles.push(angleToPoint);
        }
    }
    angles.sort((a, b) => a - b);
    const extendedAngles = angles.concat(angles.map(a => a + 360));
    let maxVisible = 0;
    let right = 0;
    for (let left = 0; left < angles.length; left++) {
        while (right < extendedAngles.length && extendedAngles[right] <= extendedAngles[left] + angle) {
            right++;
        }
        maxVisible = Math.max(maxVisible, right - left);
    }
    return maxVisible + sameLocationCount;
};
