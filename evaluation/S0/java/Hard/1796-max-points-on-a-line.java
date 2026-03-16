// Source: https://leetcode.com/problems/max-points-on-a-line/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 3
//
// Constraints:
// 1 <= points.length <= 300
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//

class Solution {
    public int maxPoints(int[][] points) {
        if (points.length <= 2) return points.length;

        int maxPointsOnLine = 1;

        for (int i = 0; i < points.length; i++) {
            Map<String, Integer> slopeCountMap = new HashMap<>();
            int duplicatePoints = 0;
            int currentMax = 0;

            for (int j = i + 1; j < points.length; j++) {
                int deltaX = points[j][0] - points[i][0];
                int deltaY = points[j][1] - points[i][1];

                if (deltaX == 0 && deltaY == 0) {
                    duplicatePoints++;
                    continue;
                }

                int gcd = gcd(deltaX, deltaY);
                deltaX /= gcd;
                deltaY /= gcd;

                String slopeKey = deltaX + "/" + deltaY;
                slopeCountMap.put(slopeKey, slopeCountMap.getOrDefault(slopeKey, 0) + 1);
                currentMax = Math.max(currentMax, slopeCountMap.get(slopeKey));
            }

            maxPointsOnLine = Math.max(maxPointsOnLine, currentMax + duplicatePoints + 1);
        }

        return maxPointsOnLine;         
    }
}
