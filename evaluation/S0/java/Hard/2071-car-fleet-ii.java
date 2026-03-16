// Source: https://leetcode.com/problems/car-fleet-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n cars traveling at different speeds in the same direction along a one-lane road. You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:
//
//
// 	positioni is the distance between the ith car and the beginning of the road in meters. It is guaranteed that positioni < positioni+1.
// 	speedi is the initial speed of the ith car in meters per second.
//
//
// For simplicity, cars can be considered as points moving along the number line. Two cars collide when they occupy the same position. Once a car collides with another car, they unite and form a single car fleet. The cars in the formed fleet will have the same position and the same speed, which is the initial speed of the slowest car in the fleet.
//
// Return an array answer, where answer[i] is the time, in seconds, at which the ith car collides with the next car, or -1 if the car does not collide with the next car. Answers within 10-5 of the actual answers are accepted.
//
// Example:
// Input: cars = [[1,2],[2,1],[4,3],[7,2]]
// Output: [1.00000,-1.00000,3.00000,-1.00000]
// Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
//
// Constraints:
// 1 <= cars.length <= 105
// 	1 <= positioni, speedi <= 106
// 	positioni < positioni+1
//

class Solution {
    public double[] getCollisionTimes(int[][] cars) {
        int n = cars.length;
        double[] res = new double[n];
        java.util.Arrays.fill(res, -1.0);
        java.util.Stack<Integer> stack = new java.util.Stack<>();

        for (int i = n - 2; i >= 0; i--) {
            int pos1 = cars[i][0], speed1 = cars[i][1];

            while (!stack.isEmpty()) {
                int j = stack.peek();
                int pos2 = cars[j][0], speed2 = cars[j][1];

                // If the current car is slower or equal in speed to the car ahead, it will never collide.
                if (speed1 <= speed2) {
                    stack.pop();
                    continue;
                }

                // Calculate the time to collide with the car ahead.
                double timeToCollide = (double) (pos2 - pos1) / (speed1 - speed2);

                // If the car ahead will collide before this car can reach it, pop it from the stack.
                if (res[j] != -1 && timeToCollide >= res[j]) {
                    stack.pop();
                } else {
                    res[i] = timeToCollide;
                    break;
                }
            }
            stack.push(i);
        }

        return res;         
    }
}
