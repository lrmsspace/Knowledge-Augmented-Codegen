// Source: https://leetcode.com/problems/rectangle-area-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner.
//
// Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.
//
// Return the total area. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
// Output: 6
// Explanation: A total area of 6 is covered by all three rectangles, as illustrated in the picture.
// From (1,1) to (2,2), the green and red rectangles overlap.
// From (1,0) to (2,3), all three rectangles overlap.
//
// Constraints:
// 1 <= rectangles.length <= 200
// 	rectanges[i].length == 4
// 	0 <= xi1, yi1, xi2, yi2 <= 109
// 	xi1 <= xi2
// 	yi1 <= yi2
// 	All rectangles have non zero area.
//

class Solution {
    public int rectangleArea(int[][] rectangles) {
        final int MOD = 1_000_000_007;
        TreeSet<Integer> xSet = new TreeSet<>();
        for (int[] rect : rectangles) {
            xSet.add(rect[0]);
            xSet.add(rect[2]);
        }
        Integer[] xArr = xSet.toArray(new Integer[0]);
        long area = 0;
        for (int i = 1; i < xArr.length; i++) {
            int x1 = xArr[i - 1];
            int x2 = xArr[i];
            List<int[]> yIntervals = new ArrayList<>();
            for (int[] rect : rectangles) {
                if (rect[0] <= x1 && rect[2] >= x2) {
                    yIntervals.add(new int[]{rect[1], rect[3]});
                }
            }
            Collections.sort(yIntervals, (a, b) -> a[0] - b[0]);
            long yCoverage = 0;
            int currStart = -1;
            int currEnd = -1;
            for (int[] interval : yIntervals) {
                if (interval[0] > currEnd) {
                    yCoverage += currEnd - currStart;
                    currStart = interval[0];
                    currEnd = interval[1];
                } else {
                    currEnd = Math.max(currEnd, interval[1]);
                }
            }
            yCoverage += currEnd - currStart;
            area = (area + yCoverage * (x2 - x1)) % MOD;
        }
        return (int) area;          
    }
}
