// Source: https://leetcode.com/problems/walking-robot-simulation/   |   Difficulty: Medium
//
// Problem Description:
// A robot on an infinite XY-plane starts at point (0, 0) facing north. The robot receives an array of integers commands, which represents a sequence of moves that it needs to execute. There are only three possible types of instructions the robot can receive:
//
//
// 	-2: Turn left 90 degrees.
// 	-1: Turn right 90 degrees.
// 	1 <= k <= 9: Move forward k units, one unit at a time.
//
//
// Some of the grid squares are obstacles. The ith obstacle is at grid point obstacles[i] = (xi, yi). If the robot runs into an obstacle, it will stay in its current location (on the block adjacent to the obstacle) and move onto the next command.
//
// Return the maximum squared Euclidean distance that the robot reaches at any point in its path (i.e. if the distance is 5, return 25).
//
// Note:
//
//
// 	There can be an obstacle at (0, 0). If this happens, the robot will ignore the obstacle until it has moved off the origin. However, it will be unable to return to (0, 0) due to the obstacle.
// 	North means +Y direction.
// 	East means +X direction.
// 	South means -Y direction.
// 	West means -X direction.
//
// Example:
// Input: commands = [4,-1,3], obstacles = []
//
// Output: 25
//
// Explanation: 
//
// The robot starts at (0, 0):
//
//
// 	Move north 4 units to (0, 4).
// 	Turn right.
// 	Move east 3 units to (3, 4).
//
//
// The furthest point the robot ever gets from the origin is (3, 4), which squared is 32 + 42 = 25 units away.
//
// Constraints:
// 1 <= commands.length <= 104
// 	commands[i] is either -2, -1, or an integer in the range [1, 9].
// 	0 <= obstacles.length <= 104
// 	-3 * 104 <= xi, yi <= 3 * 104
// 	The answer is guaranteed to be less than 231.
//

class Solution {
    public int robotSim(int[] commands, int[][] obstacles) {
        // Directions represent North, East, South, West
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int dirIndex = 0; // Start facing North
        int x = 0, y = 0;
        int maxDistanceSq = 0;

        // Store obstacles in a set for O(1) access
        Set<String> obstacleSet = new HashSet<>();
        for (int[] obs : obstacles) {
            obstacleSet.add(obs[0] + "," + obs[1]);
        }

        for (int command : commands) {
            if (command == -2) { // Turn left
                dirIndex = (dirIndex + 3) % 4;
            } else if (command == -1) { // Turn right
                dirIndex = (dirIndex + 1) % 4;
            } else { // Move forward
                for (int step = 0; step < command; step++) {
                    int nextX = x + directions[dirIndex][0];
                    int nextY = y + directions[dirIndex][1];
                    if (obstacleSet.contains(nextX + "," + nextY)) {
                        break; // Hit an obstacle
                    }
                    x = nextX;
                    y = nextY;
                    maxDistanceSq = Math.max(maxDistanceSq, x * x + y * y);
                }
            }
        }

        return maxDistanceSq;           
    }
}
