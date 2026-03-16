// Source: https://leetcode.com/problems/task-scheduler-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of positive integers tasks, representing tasks that need to be completed in order, where tasks[i] represents the type of the ith task.
//
// You are also given a positive integer space, which represents the minimum number of days that must pass after the completion of a task before another task of the same type can be performed.
//
// Each day, until all tasks have been completed, you must either:
//
//
// 	Complete the next task from tasks, or
// 	Take a break.
//
//
// Return the minimum number of days needed to complete all tasks.
//
// Example:
// Input: tasks = [1,2,1,2,3,1], space = 3
// Output: 9
// Explanation:
// One way to complete all tasks in 9 days is as follows:
// Day 1: Complete the 0th task.
// Day 2: Complete the 1st task.
// Day 3: Take a break.
// Day 4: Take a break.
// Day 5: Complete the 2nd task.
// Day 6: Complete the 3rd task.
// Day 7: Take a break.
// Day 8: Complete the 4th task.
// Day 9: Complete the 5th task.
// It can be shown that the tasks cannot be completed in less than 9 days.
//
// Constraints:
// 1 <= tasks.length <= 105
// 	1 <= tasks[i] <= 109
// 	1 <= space <= tasks.length
//
// Helpful references (internal KB):
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
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long taskSchedulerII(int* tasks, int tasksSize, int space) {
    long long day = 0;
    // Using a hash map to store the next available day for each task type
    // Since task types can be large, we use a simple array of structs to simulate a hash map
    #define HASH_SIZE 100003
    typedef struct {
        int key;
        long long value;
    } HashEntry;

    HashEntry hashMap[HASH_SIZE] = {0};

    long long getNextDay(int taskType) {
        int hashIndex = taskType % HASH_SIZE;
        while (hashMap[hashIndex].key != 0 && hashMap[hashIndex].key != taskType) {
            hashIndex = (hashIndex + 1) % HASH_SIZE;
        }
        return hashMap[hashIndex].value;
    }

    void setNextDay(int taskType, long long nextDay) {
        int hashIndex = taskType % HASH_SIZE;
        while (hashMap[hashIndex].key != 0 && hashMap[hashIndex].key != taskType) {
            hashIndex = (hashIndex + 1) % HASH_SIZE;
        }
        hashMap[hashIndex].key = taskType;
        hashMap[hashIndex].value = nextDay;
    }

    for (int i = 0; i < tasksSize; i++) {
        day++;
        long long nextAvailableDay = getNextDay(tasks[i]);
        if (day < nextAvailableDay) {
            day = nextAvailableDay;
        }
        setNextDay(tasks[i], day + space + 1);
    }

    return day;     
}
