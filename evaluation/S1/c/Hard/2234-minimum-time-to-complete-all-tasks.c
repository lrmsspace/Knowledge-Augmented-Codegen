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
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findMinimumTime(int** tasks, int tasksSize, int* tasksColSize) {
    // Sort tasks by end time
    int cmp(const void *a, const void *b) {
        int endA = (*(int**)a)[1];
        int endB = (*(int**)b)[1];
        return endA - endB;
    }
    qsort(tasks, tasksSize, sizeof(int*), cmp);

    int maxTime = 2000;
    int timeline[2001] = {0}; // timeline[i] = 1 if time i is used

    for (int i = 0; i < tasksSize; i++) {
        int start = tasks[i][0];
        int end = tasks[i][1];
        int duration = tasks[i][2];

        // Count already used time slots in the task's range
        int used = 0;
        for (int t = start; t <= end; t++) {
            if (timeline[t]) {
                used++;
            }
        }

        // Need to schedule (duration - used) more time slots
        int toSchedule = duration - used;
        for (int t = end; t >= start && toSchedule > 0; t--) {
            if (!timeline[t]) {
                timeline[t] = 1; // Mark this time slot as used
                toSchedule--;
            }
        }
    }

    // Count total used time slots
    int totalUsed = 0;
    for (int t = 1; t <= maxTime; t++) {
        if (timeline[t]) {
            totalUsed++;
        }
    }

    return totalUsed;       
}
