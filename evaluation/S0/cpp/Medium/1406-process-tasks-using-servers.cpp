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

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        vector<int> result(m);

        // Min-heap for free servers: (weight, index)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> freeServers;
        for (int i = 0; i < n; ++i) {
            freeServers.emplace(servers[i], i);
        }

        // Min-heap for busy servers: (free_time, weight, index)
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> busyServers;

        int currentTime = 0;
        for (int i = 0; i < m; ++i) {
            currentTime = max(currentTime, i);

            // Free up servers that have completed their tasks by currentTime
            while (!busyServers.empty() && get<0>(busyServers.top()) <= currentTime) {
                auto [freeTime, weight, index] = busyServers.top();
                busyServers.pop();
                freeServers.emplace(weight, index);
            }

            // If no free servers, wait until the next server is free
            if (freeServers.empty()) {
                currentTime = get<0>(busyServers.top());
                while (!busyServers.empty() && get<0>(busyServers.top()) <= currentTime) {
                    auto [freeTime, weight, index] = busyServers.top();
                    busyServers.pop();
                    freeServers.emplace(weight, index);
                }
            }

            // Assign the task to the best available server
            auto [weight, index] = freeServers.top();
            freeServers.pop();
            result[i] = index;
            busyServers.emplace(currentTime + tasks[i], weight, index);
        }

        return result;          
    }
};
