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

class Solution {
    public long maxRectangleArea(int[] xCoord, int[] yCoord) {
        int n = xCoord.length;
        Map<Integer, List<Integer>> map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            map.computeIfAbsent(xCoord[i], k -> new ArrayList<>()).add(yCoord[i]);
        }

        Set<String> pointSet = new HashSet<>();
        for (int i = 0; i < n; i++) {
            pointSet.add(xCoord[i] + "," + yCoord[i]);
        }

        long maxArea = -1;
        List<Integer> xList = new ArrayList<>(map.keySet());
        Collections.sort(xList);

        for (int i = 0; i < xList.size(); i++) {
            List<Integer> yList1 = map.get(xList.get(i));
            Collections.sort(yList1);
            for (int j = i + 1; j < xList.size(); j++) {
                List<Integer> yList2 = map.get(xList.get(j));
                Collections.sort(yList2);

                int p1 = 0, p2 = 0;
                while (p1 < yList1.size() && p2 < yList2.size()) {
                    if (yList1.get(p1).equals(yList2.get(p2))) {
                        int y = yList1.get(p1);
                        long area = (long) (xList.get(j) - xList.get(i)) * (y - getNextY(y, yList1, pointSet, xList.get(i), xList.get(j)));
                        maxArea = Math.max(maxArea, area);
                        p1++;
                        p2++;
                    } else if (yList1.get(p1) < yList2.get(p2)) {
                        p1++;
                    } else {
                        p2++;
                    }
                }
            }
        }

        return maxArea;         
    }
}
