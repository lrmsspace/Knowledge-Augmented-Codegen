// Source: https://leetcode.com/problems/asteroid-collision/   |   Difficulty: Medium
//
// Problem Description:
// We are given an array asteroids of integers representing asteroids in a row. The indices of the asteriod in the array represent their relative position in space.
//
// For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
//
// Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.
//
// Example:
// Input: asteroids = [5,10,-5]
// Output: [5,10]
// Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
//
// Constraints:
// 2 <= asteroids.length <= 104
// 	-1000 <= asteroids[i] <= 1000
// 	asteroids[i] != 0
//

/**
 * @param {number[]} asteroids
 * @return {number[]}
 */
var asteroidCollision = function(asteroids) {
    const stack = [];
    for (let asteroid of asteroids) {
        let destroyed = false;
        while (stack.length > 0 && asteroid < 0 && stack[stack.length - 1] > 0) {
            if (stack[stack.length - 1] < -asteroid) {
                stack.pop();
                continue;
            } else if (stack[stack.length - 1] === -asteroid) {
                stack.pop();
            }
            destroyed = true;
            break;
        }
        if (!destroyed) {
            stack.push(asteroid);
        }
    }
    return stack;
};