// Source: https://leetcode.com/problems/pass-the-pillow/   |   Difficulty: Easy
//
// Problem Description:
// There are n people standing in a line labeled from 1 to n. The first person in the line is holding a pillow initially. Every second, the person holding the pillow passes it to the next person standing in the line. Once the pillow reaches the end of the line, the direction changes, and people continue passing the pillow in the opposite direction.
//
//
// 	For example, once the pillow reaches the nth person they pass it to the n - 1th person, then to the n - 2th person and so on.
//
//
// Given the two positive integers n and time, return the index of the person holding the pillow after time seconds.
//
// Example:
// Input: n = 4, time = 5
// Output: 2
// Explanation: People pass the pillow in the following way: 1 -> 2 -> 3 -> 4 -> 3 -> 2.
// After five seconds, the 2nd person is holding the pillow.
//
// Constraints:
// 2 <= n <= 1000
// 	1 <= time <= 1000
//
//
//  
// Note: This question is the same as  3178: Find the Child Who Has the Ball After K Seconds.
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
 * @param {number} n
 * @param {number} time
 * @return {number}
 */
var passThePillow = function(n, time) {
    const cycleLength = 2 * (n - 1);
    const timeInCycle = time % cycleLength;
    
    if (timeInCycle < n - 1) {
        return timeInCycle + 1;
    } else {
        return 2 * n - timeInCycle - 2;
    }
};
