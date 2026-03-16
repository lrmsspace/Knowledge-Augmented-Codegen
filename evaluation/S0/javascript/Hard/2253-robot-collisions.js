// Source: https://leetcode.com/problems/robot-collisions/   |   Difficulty: Hard
//
// Problem Description:
// There are n 1-indexed robots, each having a position on a line, health, and movement direction.
//
// You are given 0-indexed integer arrays positions, healths, and a string directions (directions[i] is either 'L' for left or 'R' for right). All integers in positions are unique.
//
// All robots start moving on the line simultaneously at the same speed in their given directions. If two robots ever share the same position while moving, they will collide.
//
// If two robots collide, the robot with lower health is removed from the line, and the health of the other robot decreases by one. The surviving robot continues in the same direction it was going. If both robots have the same health, they are both removed from the line.
//
// Your task is to determine the health of the robots that survive the collisions, in the same order that the robots were given, i.e. final health of robot 1 (if survived), final health of robot 2 (if survived), and so on. If there are no survivors, return an empty array.
//
// Return an array containing the health of the remaining robots (in the order they were given in the input), after no further collisions can occur.
//
// Note: The positions may be unsorted.
//
// Example:
// Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
// Output: [2,17,9,15,10]
// Explanation: No collision occurs in this example, since all robots are moving in the same direction. So, the health of the robots in order from the first robot is returned, [2, 17, 9, 15, 10].
//
// Constraints:
// 1 <= positions.length == healths.length == directions.length == n <= 105
// 	1 <= positions[i], healths[i] <= 109
// 	directions[i] == 'L' or directions[i] == 'R'
// 	All values in positions are distinct
//

/**
 * @param {number[]} positions
 * @param {number[]} healths
 * @param {string} directions
 * @return {number[]}
 */
var survivedRobotsHealths = function(positions, healths, directions) {
    const n = positions.length;
    const robots = [];
    for (let i = 0; i < n; i++) {
        robots.push({ position: positions[i], health: healths[i], direction: directions[i], index: i });
    }
    robots.sort((a, b) => a.position - b.position);
    const stack = [];
    for (const robot of robots) {
        if (robot.direction === 'R') {
            stack.push(robot);
        } else {
            while (stack.length > 0 && stack[stack.length - 1].direction === 'R') {
                const top = stack[stack.length - 1];
                if (top.health < robot.health) {
                    robot.health -= 1;
                    stack.pop();
                }
                else if (top.health > robot.health) {
                    top.health -= 1;
                    break;
                }
                else {
                    stack.pop();
                    break;
                }
            }
        }
    }
    const result = new Array(n).fill(0);
    for (const robot of stack) {
        result[robot.index] = robot.health;
    }
    return result.filter(health => health > 0); 
};
