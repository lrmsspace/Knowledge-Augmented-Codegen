// Source: https://leetcode.com/problems/single-threaded-cpu/   |   Difficulty: Medium
//
// Problem Description:
// You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.
//
// You have a single-threaded CPU that can process at most one task at a time and will act in the following way:
//
//
// 	If the CPU is idle and there are no available tasks to process, the CPU remains idle.
// 	If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
// 	Once a task is started, the CPU will process the entire task without stopping.
// 	The CPU can finish a task then start a new one instantly.
//
//
// Return the order in which the CPU will process the tasks.
//
// Example:
// Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
// Output: [0,2,3,1]
// Explanation: The events go as follows: 
// - At time = 1, task 0 is available to process. Available tasks = {0}.
// - Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
// - At time = 2, task 1 is available to process. Available tasks = {1}.
// - At time = 3, task 2 is available to process. Available tasks = {1, 2}.
// - Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
// - At time = 4, task 3 is available to process. Available tasks = {1, 3}.
// - At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
// - At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
// - At time = 10, the CPU finishes task 1 and becomes idle.
//
// Constraints:
// tasks.length == n
// 	1 <= n <= 105
// 	1 <= enqueueTimei, processingTimei <= 109
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getOrder(int** tasks, int tasksSize, int* tasksColSize, int* returnSize) {
    // Step 1: Create an array of task indices and sort by enqueue time
    int* indices = (int*)malloc(tasksSize * sizeof(int));
    for (int i = 0; i < tasksSize; i++) {
        indices[i] = i;
    }
    // Sort indices based on enqueue time
    qsort(indices, tasksSize, sizeof(int), compareEnqueueTime);
    
    // Step 2: Use a min-heap to manage available tasks based on processing time and index
    typedef struct {
        int processingTime;
        int index;
    } TaskInfo;

    TaskInfo* minHeap = (TaskInfo*)malloc(tasksSize * sizeof(TaskInfo));
    int heapSize = 0;

    int* result = (int*)malloc(tasksSize * sizeof(int));
    int resultIndex = 0;
    
    long long currentTime = 0;
    int taskPointer = 0;

    while (resultIndex < tasksSize) {
        // Add all tasks that are now available to the min-heap
        while (taskPointer < tasksSize && tasks[indices[taskPointer]][0] <= currentTime) {
            minHeap[heapSize++] = (TaskInfo){tasks[indices[taskPointer]][1], indices[taskPointer]};
            taskPointer++;
        }
        
        if (heapSize > 0) {
            // Get the task with the shortest processing time (and smallest index if tie)
            TaskInfo currentTask = minHeap[0];
            result[resultIndex++] = currentTask.index;
            currentTime += currentTask.processingTime;

            // Remove the task from the min-heap            minHeap[0] = minHeap[--heapSize];
            // Re-heapify the min-heap
            qsort(minHeap, heapSize, sizeof(TaskInfo), compareTaskInfo);
        } else {
            // If no tasks are available, move to the next task's enqueue time
            currentTime = tasks[indices[taskPointer]][0];
        }
    }
    *returnSize = tasksSize;
    free(indices);
    free(minHeap);
    return result;
}
