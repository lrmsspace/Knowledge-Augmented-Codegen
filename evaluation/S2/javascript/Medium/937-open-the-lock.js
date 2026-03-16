// Source: https://leetcode.com/problems/open-the-lock/   |   Difficulty: Medium
//
// Problem Description:
// You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.
//
// The lock initially starts at '0000', a string representing the state of the 4 wheels.
//
// You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.
//
// Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.
//
// Example:
// Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
// Output: 6
// Explanation: 
// A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
// Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
// because the wheels of the lock become stuck after the display becomes the dead end "0102".
//
// Constraints:
// 1 <= deadends.length <= 500
// 	deadends[i].length == 4
// 	target.length == 4
// 	target will not be in the list deadends.
// 	target and deadends[i] consist of digits only.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} deadends
 * @param {string} target
 * @return {number}
 */
var openLock = function(deadends, target) {
    const deadSet = new Set(deadends);
    if (deadSet.has('0000')) return -1;
    
    const queue = ['0000'];
    const visited = new Set(['0000']);
    let steps = 0;
    
    while (queue.length) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const current = queue.shift();
            if (current === target) return steps;
            for (const next of getNextStates(current)) {
                if (!deadSet.has(next) && !visited.has(next)) {
                    visited.add(next);
                    queue.push(next);
                }
            }
        }
        steps++;
    }
    
    return -1;
};
