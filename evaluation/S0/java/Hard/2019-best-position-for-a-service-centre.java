// Source: https://leetcode.com/problems/best-position-for-a-service-centre/   |   Difficulty: Hard
//
// Problem Description:
// A delivery company wants to build a new service center in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new center in a position such that the sum of the euclidean distances to all customers is minimum.
//
// Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.
//
// In other words, you need to choose the position of the service center [xcentre, ycentre] such that the following formula is minimized:
//
// Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: positions = [[0,1],[1,0],[1,2],[2,1]]
// Output: 4.00000
// Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
//
// Constraints:
// 1 <= positions.length <= 50
// 	positions[i].length == 2
// 	0 <= xi, yi <= 100
//

class Solution {
    public double getMinDistSum(int[][] positions) {
        double x = 50.0, y = 50.0;
        double step = 50.0;
        double ans = Double.MAX_VALUE;

        for (int iter = 0; iter < 100; iter++) {
            double bestX = x, bestY = y;
            for (int dirX = -1; dirX <= 1; dirX++) {
                for (int dirY = -1; dirY <= 1; dirY++) {
                    if (dirX == 0 && dirY == 0) continue;
                    double newX = x + dirX * step;
                    double newY = y + dirY * step;
                    double distSum = 0.0;
                    for (int[] pos : positions) {
                        distSum += Math.sqrt((newX - pos[0]) * (newX - pos[0]) + (newY - pos[1]) * (newY - pos[1]));
                    }
                    if (distSum < ans) {
                        ans = distSum;
                        bestX = newX;
                        bestY = newY;
                    }
                }
            }
            x = bestX;
            y = bestY;
            step *= 0.8;
        }

        return ans;                 
    }
}
