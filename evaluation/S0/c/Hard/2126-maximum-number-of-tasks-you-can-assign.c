// Source: https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/   |   Difficulty: Hard
//
// Problem Description:
// You have n tasks and m workers. Each task has a strength requirement stored in a 0-indexed integer array tasks, with the ith task requiring tasks[i] strength to complete. The strength of each worker is stored in a 0-indexed integer array workers, with the jth worker having workers[j] strength. Each worker can only be assigned to a single task and must have a strength greater than or equal to the task's strength requirement (i.e., workers[j] >= tasks[i]).
//
// Additionally, you have pills magical pills that will increase a worker's strength by strength. You can decide which workers receive the magical pills, however, you may only give each worker at most one magical pill.
//
// Given the 0-indexed integer arrays tasks and workers and the integers pills and strength, return the maximum number of tasks that can be completed.
//
// Example:
// Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
// Output: 3
// Explanation:
// We can assign the magical pill and tasks as follows:
// - Give the magical pill to worker 0.
// - Assign worker 0 to task 2 (0 + 1 >= 1)
// - Assign worker 1 to task 1 (3 >= 2)
// - Assign worker 2 to task 0 (3 >= 3)
//
// Constraints:
// n == tasks.length
// 	m == workers.length
// 	1 <= n, m <= 5 * 104
// 	0 <= pills <= m
// 	0 <= tasks[i], workers[j], strength <= 109
//

int maxTaskAssign(int* tasks, int tasksSize, int* workers, int workersSize, int pills, int strength) {
    // Sort tasks and workers
    qsort(tasks, tasksSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    qsort(workers, workersSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int left = 0, right = (tasksSize < workersSize) ? tasksSize : workersSize;
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int pillsLeft = pills;
        int taskIdx = mid - 1;
        int workerIdx = workersSize - 1;
        int canAssign = 1;

        while (taskIdx >= 0) {
            if (workerIdx < 0) {
                canAssign = 0;
                break;
            }
            if (workers[workerIdx] >= tasks[taskIdx]) {
                workerIdx--;
                taskIdx--;
            } else {
                if (pillsLeft > 0 && workers[workerIdx] + strength >= tasks[taskIdx]) {
                    pillsLeft--;
                    workerIdx--;
                    taskIdx--;
                } else {
                    canAssign = 0;
                    break;
                }
            }
        }

        if (canAssign) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;      
}
