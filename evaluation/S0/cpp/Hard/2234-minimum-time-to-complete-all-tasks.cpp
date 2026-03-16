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

class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        const int MAX_TIME = 2005;
        vector<int> timeline(MAX_TIME, 0);
        
        // Sort tasks by end time
        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        
        int totalOnTime = 0;
        
        for (const auto& task : tasks) {
            int start = task[0];
            int end = task[1];
            int duration = task[2];
            
            // Count already scheduled time for this task
            int alreadyScheduled = 0;
            for (int t = start; t <= end; ++t) {
                if (timeline[t] == 1) {
                    alreadyScheduled++;
                }
            }
            
            int remainingDuration = duration - alreadyScheduled;
            if (remainingDuration > 0) {
                // Schedule remaining time from the end backwards
                for (int t = end; t >= start && remainingDuration > 0; --t) {
                    if (timeline[t] == 0) {
                        timeline[t] = 1;
                        totalOnTime++;
                        remainingDuration--;
                    }
                }
            }
        }
        
        return totalOnTime;         
    }
};
