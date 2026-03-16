// Source: https://leetcode.com/problems/number-of-boomerangs/   |   Difficulty: Medium
//
// Problem Description:
// You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
//
// Return the number of boomerangs.
//
// Example:
// Input: points = [[0,0],[1,0],[2,0]]
// Output: 2
// Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
//
// Constraints:
// n == points.length
// 	1 <= n <= 500
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//

class Solution {
    public int numberOfBoomerangs(int[][] points) {
        int boomerangCount = 0;

        for (int[] pointI : points) {
            Map<Double, Integer> distanceCountMap = new HashMap<>();

            for (int[] pointJ : points) {
                if (pointI == pointJ) continue;

                double distance = calculateDistance(pointI, pointJ);
                distanceCountMap.put(distance, distanceCountMap.getOrDefault(distance, 0) + 1);
            }

            for (int count : distanceCountMap.values()) {
                if (count > 1) {
                    boomerangCount += count * (count - 1);
                }
            }
        }

        return boomerangCount;          
    }
}
