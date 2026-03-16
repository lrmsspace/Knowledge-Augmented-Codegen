// Source: https://leetcode.com/problems/process-tasks-using-servers/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays servers and tasks of lengths n​​​​​​ and m​​​​​​ respectively. servers[i] is the weight of the i​​​​​​th​​​​ server, and tasks[j] is the time needed to process the j​​​​​​th​​​​ task in seconds.
//
// Tasks are assigned to the servers using a task queue. Initially, all servers are free, and the queue is empty.
//
// At second j, the jth task is inserted into the queue (starting with the 0th task being inserted at second 0). As long as there are free servers and the queue is not empty, the task in the front of the queue will be assigned to a free server with the smallest weight, and in case of a tie, it is assigned to a free server with the smallest index.
//
// If there are no free servers and the queue is not empty, we wait until a server becomes free and immediately assign the next task. If multiple servers become free at the same time, then multiple tasks from the queue will be assigned in order of insertion following the weight and index priorities above.
//
// A server that is assigned task j at second t will be free again at second t + tasks[j].
//
// Build an array ans​​​​ of length m, where ans[j] is the index of the server the j​​​​​​th task will be assigned to.
//
// Return the array ans​​​​.
//
// Example:
// Input: servers = [3,3,2], tasks = [1,2,3,2,1,2]
// Output: [2,2,0,2,1,2]
// Explanation: Events in chronological order go as follows:
// - At second 0, task 0 is added and processed using server 2 until second 1.
// - At second 1, server 2 becomes free. Task 1 is added and processed using server 2 until second 3.
// - At second 2, task 2 is added and processed using server 0 until second 5.
// - At second 3, server 2 becomes free. Task 3 is added and processed using server 2 until second 5.
// - At second 4, task 4 is added and processed using server 1 until second 5.
// - At second 5, all servers become free. Task 5 is added and processed using server 2 until second 7.
//
// Constraints:
// servers.length == n
// 	tasks.length == m
// 	1 <= n, m <= 2 * 105
// 	1 <= servers[i], tasks[j] <= 2 * 105
//

/**
 * @param {number[]} servers
 * @param {number[]} tasks
 * @return {number[]}
 */
var assignTasks = function(servers, tasks) {
    const n = servers.length;
    const m = tasks.length;
    const freeServers = new MinPriorityQueue({ priority: (x) => [x.weight, x.index] });
    const busyServers = new MinPriorityQueue({ priority: (x) => x.freeTime });
    const result = Array(m);
    for (let i = 0; i < n; i++) {
        freeServers.enqueue({ weight: servers[i], index: i });
    }
    let currentTime = 0;
    for (let i = 0; i < m; i++) {
        currentTime = Math.max(currentTime, i);
        while (!busyServers.isEmpty() && busyServers.front().element.freeTime <= currentTime) {
            const server = busyServers.dequeue().element;
            freeServers.enqueue({ weight: servers[server.index], index: server.index });
        }
        if (freeServers.isEmpty()) {
            currentTime = busyServers.front().element.freeTime;
            while (!busyServers.isEmpty() && busyServers.front().element.freeTime <= currentTime) {
                const server = busyServers.dequeue().element;
                freeServers.enqueue({ weight: servers[server.index], index: server.index });
            }
        }
        const server = freeServers.dequeue().element;
        result[i] = server.index;
        busyServers.enqueue({ freeTime: currentTime + tasks[i], index: server.index });
    }
    return result;
};