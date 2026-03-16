// Source: https://leetcode.com/problems/minimum-time-to-complete-all-tasks/   |   Difficulty: Hard
//
// Problem Description:
// There is a computer that can run an unlimited number of tasks at the same time. You are given a 2D integer array tasks where tasks[i] = [starti, endi, durationi] indicates that the ith task should run for a total of durationi seconds (not necessarily continuous) within the inclusive time range [starti, endi].
//
// You may turn on the computer only when it needs to run a task. You can also turn it off if it is idle.
//
// Return the minimum time during which the computer should be turned on to complete all tasks.
//
// Example:
// Input: tasks = [[2,3,1],[4,5,1],[1,5,2]]
// Output: 2
// Explanation: 
// - The first task can be run in the inclusive time range [2, 2].
// - The second task can be run in the inclusive time range [5, 5].
// - The third task can be run in the two inclusive time ranges [2, 2] and [5, 5].
// The computer will be on for a total of 2 seconds.
//
// Constraints:
// 1 <= tasks.length <= 2000
// 	tasks[i].length == 3
// 	1 <= starti, endi <= 2000
// 	1 <= durationi <= endi - starti + 1
//

/**
 * @param {number[][]} tasks
 * @return {number}
 */
var findMinimumTime = function(tasks) {
    tasks.sort((a, b) => a[1] - b[1]);
    const timeSlots = new Set();
    for (const [start, end, duration] of tasks) {
        let count = 0;
        for (let t = start; t <= end; t++) {
            if (timeSlots.has(t)) {
                count++;
            }
        }
        for (let t = end; t >= start && count < duration; t--) {
            if (!timeSlots.has(t)) {
                timeSlots.add(t);
                count++;
            }
        }
    }
    return timeSlots.size;  
};
