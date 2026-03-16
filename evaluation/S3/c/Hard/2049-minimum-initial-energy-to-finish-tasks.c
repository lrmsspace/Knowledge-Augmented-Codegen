// Source: https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array tasks where tasks[i] = [actuali, minimumi]:
//
//
// 	actuali is the actual amount of energy you spend to finish the ith task.
// 	minimumi is the minimum amount of energy you require to begin the ith task.
//
//
// For example, if the task is [10, 12] and your current energy is 11, you cannot start this task. However, if your current energy is 13, you can complete this task, and your energy will be 3 after finishing it.
//
// You can finish the tasks in any order you like.
//
// Return the minimum initial amount of energy you will need to finish all the tasks.
//
// Example:
// Input: tasks = [[1,2],[2,4],[4,8]]
// Output: 8
// Explanation:
// Starting with 8 energy, we finish the tasks in the following order:
//     - 3rd task. Now energy = 8 - 4 = 4.
//     - 2nd task. Now energy = 4 - 2 = 2.
//     - 1st task. Now energy = 2 - 1 = 1.
// Notice that even though we have leftover energy, starting with 7 energy does not work because we cannot do the 3rd task.
//
// Constraints:
// 1 <= tasks.length <= 105
// 	1 <= actual​i <= minimumi <= 104
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumEffort(int** tasks, int tasksSize, int* tasksColSize) {
    // Sort tasks based on the difference between minimum energy and actual energy in descending order
    for (int i = 0; i < tasksSize - 1; i++) {
        for (int j = 0; j < tasksSize - i - 1; j++) {
            int diff1 = tasks[j][1] - tasks[j][0];
            int diff2 = tasks[j + 1][1] - tasks[j + 1][0];
            if (diff1 < diff2) {
                // Swap tasks[j] and tasks[j + 1]
                int* temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    int energy = 0;
    int currentEnergy = 0;

    // Calculate the minimum initial energy required
    for (int i = 0; i < tasksSize; i++) {
        if (currentEnergy < tasks[i][1]) {
            energy += tasks[i][1] - currentEnergy;
            currentEnergy = tasks[i][1];
        }
        currentEnergy -= tasks[i][0];
    }

    return energy;      
}
