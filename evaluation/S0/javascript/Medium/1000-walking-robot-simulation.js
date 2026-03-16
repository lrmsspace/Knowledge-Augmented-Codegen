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

/**
 * @param {number[]} commands
 * @param {number[][]} obstacles
 * @return {number}
 */
var robotSim = function(commands, obstacles) {
    const obstacleSet = new Set(obstacles.map(([x, y]) => `${x},${y}`));        
    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]; // North, East, South, West
    let x = 0, y = 0, dirIndex = 0, maxDistanceSq = 0;
    for (const command of commands) {       
        if (command === -2) { // Turn left
            dirIndex = (dirIndex + 3) % 4;
        } else if (command === -1) { // Turn right
            dirIndex = (dirIndex + 1) % 4;
        } else { // Move forward
            const [dx, dy] = directions[dirIndex];
            for (let step = 0; step < command; step++) {
                const nextX = x + dx;
                const nextY = y + dy;
                if (obstacleSet.has(`${nextX},${nextY}`)) {
                    break;
                }
                x = nextX;
                y = nextY;
                maxDistanceSq = Math.max(maxDistanceSq, x * x + y * y);
            }
        }
    }
    return maxDistanceSq;
};  