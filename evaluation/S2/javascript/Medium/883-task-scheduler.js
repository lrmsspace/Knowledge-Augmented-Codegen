// Source: https://leetcode.com/problems/task-scheduler/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n. Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least n intervals between two tasks with the same label.
//
// Return the minimum number of CPU intervals required to complete all tasks.
//
// Example:
// Input: tasks = ["A","A","A","B","B","B"], n = 2
//
// Output: 8
//
// Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
//
// After completing task A, you must wait two intervals before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle. By the 4th interval, you can do A again as 2 intervals have passed.
//
// Constraints:
// 1 <= tasks.length <= 104
// 	tasks[i] is an uppercase English letter.
// 	0 <= n <= 100
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
 * @param {character[]} tasks
 * @param {number} n
 * @return {number}
 */
var leastInterval = function(tasks, n) {
    const freq = new Array(26).fill(0);
    for (const task of tasks) {
        freq[task.charCodeAt(0) - 'A'.charCodeAt(0)]++;
    }
    const maxFreq = Math.max(...freq);
    let maxFreqCount = 0;
    for (const f of freq) {
        if (f === maxFreq) maxFreqCount++;
    }
    const minIntervals = (maxFreq - 1) * (n + 1) + maxFreqCount;
    return Math.max(minIntervals, tasks.length);
};
