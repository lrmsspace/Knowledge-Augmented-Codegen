// Source: https://leetcode.com/problems/car-fleet/   |   Difficulty: Medium
//
// Problem Description:
// There are n cars at given miles away from the starting mile 0, traveling to reach the mile target.
//
// You are given two integer arrays position and speed, both of length n, where position[i] is the starting mile of the ith car and speed[i] is the speed of the ith car in miles per hour.
//
// A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car.
//
// A car fleet is a single car or a group of cars driving next to each other. The speed of the car fleet is the minimum speed of any car in the fleet.
//
// If a car catches up to a car fleet at the mile target, it will still be considered as part of the car fleet.
//
// Return the number of car fleets that will arrive at the destination.
//
// Example:
// Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
//
// Output: 3
//
// Explanation:
//
//
// 	The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each other at 12. The fleet forms at target.
// 	The car starting at 0 (speed 1) does not catch up to any other car, so it is a fleet by itself.
// 	The cars starting at 5 (speed 1) and 3 (speed 3) become a fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches target.
//
// Constraints:
// n == position.length == speed.length
// 	1 <= n <= 105
// 	0 < target <= 106
// 	0 <= position[i] < target
// 	All the values of position are unique.
// 	0 < speed[i] <= 106
//

class Solution {
    public int carFleet(int target, int[] position, int[] speed) {
        int n = position.length;
        double[][] cars = new double[n][2];

        for (int i = 0; i < n; i++) {
            cars[i][0] = position[i];
            cars[i][1] = (double)(target - position[i]) / speed[i];
        }

        Arrays.sort(cars, (a, b) -> Double.compare(b[0], a[0]));

        int fleets = 0;
        double lastTime = 0.0;

        for (int i = 0; i < n; i++) {
            double time = cars[i][1];
            if (time > lastTime) {
                fleets++;
                lastTime = time;
            }
        }

        return fleets;          
    }
}
