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

class Solution {
    public int[] countRectangles(int[][] rectangles, int[][] points) {
        // Create an array of lists to group rectangle lengths by their heights
        List<Integer>[] heightToLengths = new ArrayList[101];
        for (int i = 1; i <= 100; i++) {
            heightToLengths[i] = new ArrayList<>();
        }

        // Populate the lists with rectangle lengths
        for (int[] rect : rectangles) {
            int length = rect[0];
            int height = rect[1];
            heightToLengths[height].add(length);
        }

        // Sort each list of lengths for binary search
        for (int i = 1; i <= 100; i++) {
            Collections.sort(heightToLengths[i]);
        }

        int[] result = new int[points.length];

        // For each point, count the number of rectangles containing it
        for (int i = 0; i < points.length; i++) {
            int x = points[i][0];
            int y = points[i][1];
            int count = 0;

            // Check rectangles with heights >= y
            for (int h = y; h <= 100; h++) {
                List<Integer> lengths = heightToLengths[h];
                if (!lengths.isEmpty()) {
                    // Binary search to find the first length >= x
                    int left = 0, right = lengths.size();
                    while (left < right) {
                        int mid = left + (right - left) / 2;
                        if (lengths.get(mid) >= x) {
                            right = mid;
                        } else {
                            left = mid + 1;
                        }
                    }
                    count += lengths.size() - left;
                }
            }
            result[i] = count;
        }

        return result;          
    }
}
