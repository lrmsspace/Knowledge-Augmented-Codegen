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
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
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
    // Step 1: Create an array to store the tasks with their original indices
    int** indexedTasks = (int**)malloc(tasksSize * sizeof(int*));
    for (int i = 0; i < tasksSize; i++) {
        indexedTasks[i] = (int*)malloc(3 * sizeof(int));
        indexedTasks[i][0] = tasks[i][0]; // enqueueTime
        indexedTasks[i][1] = tasks[i][1]; // processingTime
        indexedTasks[i][2] = i;           // original index
    }
    
    // Step 2: Sort the tasks by enqueue time
    qsort(indexedTasks, tasksSize, sizeof(int*), [](const void* a, const void* b) {
        int* taskA = *(int**)a;
        int* taskB = *(int**)b;
        return taskA[0] - taskB[0];
    });
    
    // Step 3: Use a min-heap to manage available tasks based on processing time and index
    typedef struct {
        int processingTime;
        int index;
    } Task;
    
    Task* minHeap = (Task*)malloc(tasksSize * sizeof(Task));
    int heapSize = 0;
    
    // Helper functions for the min-heap
    void swap(Task* a, Task* b) {
        Task temp = *a;
        *a = *b;
        *b = temp;
    }
    
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (minHeap[index].processingTime < minHeap[parentIndex].processingTime ||
                (minHeap[index].processingTime == minHeap[parentIndex].processingTime && minHeap[index].index < minHeap[parentIndex].index)) {
                swap(&minHeap[index], &minHeap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }
    
    void heapifyDown(int index) {
        int smallest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        
        if (leftChild < heapSize && 
            (minHeap[leftChild].processingTime < minHeap[smallest].processingTime ||
             (minHeap[leftChild].processingTime == minHeap[smallest].processingTime && minHeap[leftChild].index < minHeap[smallest].index))) {
            smallest = leftChild;
        }
        if (rightChild < heapSize && 
            (minHeap[rightChild].processingTime < minHeap[smallest].processingTime ||
             (minHeap[rightChild].processingTime == minHeap[smallest].processingTime && minHeap[rightChild].index < minHeap[smallest].index))) {
            smallest = rightChild;
        }
        if (smallest != index) {
            swap(&minHeap[index], &minHeap[smallest]);
            heapifyDown(smallest);
        }
    }
    
    // Step 4: Process tasks in order
    int* result = (int*)malloc(tasksSize * sizeof(int));
    int resultIndex = 0;
    int currentTime = 0;
    int taskIndex = 0;
    
    while (taskIndex < tasksSize || heapSize > 0) {
        // Add all tasks that are available at the current time to the heap
        while (taskIndex < tasksSize && indexedTasks[taskIndex][0] <= currentTime) {
            minHeap[heapSize].processingTime = indexedTasks[taskIndex][1];
            minHeap[heapSize].index = indexedTasks[taskIndex][2];
            heapifyUp(heapSize);
            heapSize++;
            taskIndex++;
        }
        
        if (heapSize > 0) {
            // Process the task with the smallest processing time and smallest index
            Task currentTask = minHeap[0];
            result[resultIndex++] = currentTask.index;
            currentTime += currentTask.processingTime;
            
            // Remove the processed task from the heap
            minHeap[0] = minHeap[--heapSize];
            heapifyDown(0);
        } else if (taskIndex < tasksSize) {
            // If no tasks are available, jump to the next task's enqueue time
            currentTime = indexedTasks[taskIndex][0];
        }
    }
    
    *returnSize = tasksSize;
    return result;
}
