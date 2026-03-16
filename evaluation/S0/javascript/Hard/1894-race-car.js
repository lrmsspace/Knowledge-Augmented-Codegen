// Source: https://leetcode.com/problems/race-car/   |   Difficulty: Hard
//
// Problem Description:
// Your car starts at position 0 and speed +1 on an infinite number line. Your car can go into negative positions. Your car drives automatically according to a sequence of instructions 'A' (accelerate) and 'R' (reverse):
//
//
// 	When you get an instruction 'A', your car does the following:
//
// 	
// 		position += speed
// 		speed *= 2
// 	
// 	
// 	When you get an instruction 'R', your car does the following:
// 	
// 		If your speed is positive then speed = -1
// 		otherwise speed = 1
// 	
// 	Your position stays the same.
//
//
// For example, after commands "AAR", your car goes to positions 0 --> 1 --> 3 --> 3, and your speed goes to 1 --> 2 --> 4 --> -1.
//
// Given a target position target, return the length of the shortest sequence of instructions to get there.
//
// Example:
// Input: target = 3
// Output: 2
// Explanation: 
// The shortest instruction sequence is "AA".
// Your position goes from 0 --> 1 --> 3.
//
// Constraints:
// 1 <= target <= 104
//

/**
 * @param {number} target
 * @return {number}
 */
var racecar = function(target) {
    const queue = [[0, 1]];
    const visited = new Set();
    visited.add('0,1');
    let steps = 0;
    while (queue.length > 0) {
        const nextQueue = [];
        for (const [position, speed] of queue) {
            if (position === target) {
                return steps;
            }
            let nextPosition = position + speed;
            let nextSpeed = speed * 2;
            let key = `${nextPosition},${nextSpeed}`;
            if (!visited.has(key) && nextPosition > 0 && nextPosition < 2 * target) {
                visited.add(key);
                nextQueue.push([nextPosition, nextSpeed]);
            }
            nextSpeed = speed > 0 ? -1 : 1;
            key = `${position},${nextSpeed}`;
            if (!visited.has(key)) {
                visited.add(key);
                nextQueue.push([position, nextSpeed]);
            }
        }
        queue.length = 0;
        for (const item of nextQueue) {
            queue.push(item);
        }
        steps++;
    }
    return -1;
};
