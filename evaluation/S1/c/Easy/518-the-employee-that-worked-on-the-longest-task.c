// Source: https://leetcode.com/problems/the-employee-that-worked-on-the-longest-task/   |   Difficulty: Easy
//
// Problem Description:
// There are n employees, each with a unique id from 0 to n - 1.
//
// You are given a 2D integer array logs where logs[i] = [idi, leaveTimei] where:
//
//
// 	idi is the id of the employee that worked on the ith task, and
// 	leaveTimei is the time at which the employee finished the ith task. All the values leaveTimei are unique.
//
//
// Note that the ith task starts the moment right after the (i - 1)th task ends, and the 0th task starts at time 0.
//
// Return the id of the employee that worked the task with the longest time. If there is a tie between two or more employees, return the smallest id among them.
//
// Example:
// Input: n = 10, logs = [[0,3],[2,5],[0,9],[1,15]]
// Output: 1
// Explanation: 
// Task 0 started at 0 and ended at 3 with 3 units of times.
// Task 1 started at 3 and ended at 5 with 2 units of times.
// Task 2 started at 5 and ended at 9 with 4 units of times.
// Task 3 started at 9 and ended at 15 with 6 units of times.
// The task with the longest time is task 3 and the employee with id 1 is the one that worked on it, so we return 1.
//
// Constraints:
// 2 <= n <= 500
// 	1 <= logs.length <= 500
// 	logs[i].length == 2
// 	0 <= idi <= n - 1
// 	1 <= leaveTimei <= 500
// 	idi != idi+1
// 	leaveTimei are sorted in a strictly increasing order.
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int hardestWorker(int n, int** logs, int logsSize, int* logsColSize) {
    int maxTime = 0;
    int employeeId = n; // Initialize to maximum possible id + 1

    int previousLeaveTime = 0;

    for (int i = 0; i < logsSize; i++) {
        int currentEmployeeId = logs[i][0];
        int currentLeaveTime = logs[i][1];

        int taskDuration = currentLeaveTime - previousLeaveTime;

        if (taskDuration > maxTime) {
            maxTime = taskDuration;
            employeeId = currentEmployeeId;
        } else if (taskDuration == maxTime && currentEmployeeId < employeeId) {
            employeeId = currentEmployeeId;
        }

        previousLeaveTime = currentLeaveTime;
    }

    return employeeId;      
}
