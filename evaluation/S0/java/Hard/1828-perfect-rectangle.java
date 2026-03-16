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

class Solution {
    public boolean isRectangleCover(int[][] rectangles) {
        int minX = Integer.MAX_VALUE, minY = Integer.MAX_VALUE;
        int maxX = Integer.MIN_VALUE, maxY = Integer.MIN_VALUE;
        int area = 0;
        Set<String> points = new HashSet<>();

        for (int[] rect : rectangles) {
            int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];

            minX = Math.min(minX, x1);
            minY = Math.min(minY, y1);
            maxX = Math.max(maxX, x2);
            maxY = Math.max(maxY, y2);

            area += (x2 - x1) * (y2 - y1);

            String[] cornerPoints = {
                x1 + "," + y1,
                x1 + "," + y2,
                x2 + "," + y1,
                x2 + "," + y2
            };

            for (String point : cornerPoints) {
                if (!points.add(point)) {
                    points.remove(point);
                }
            }
        }

        String[] expectedCorners = {
            minX + "," + minY,
            minX + "," + maxY,
            maxX + "," + minY,
            maxX + "," + maxY
        };

        if (points.size() != 4) {
            return false;
        }

        for (String corner : expectedCorners) {
            if (!points.contains(corner)) {
                return false;
            }
        }

        int expectedArea = (maxX - minX) * (maxY - minY);
        return area == expectedArea;            
    }
}
