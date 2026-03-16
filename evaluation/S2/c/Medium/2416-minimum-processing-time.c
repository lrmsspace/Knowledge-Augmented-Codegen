// Source: https://leetcode.com/problems/minimum-processing-time/   |   Difficulty: Medium
//
// Problem Description:
// You have a certain number of processors, each having 4 cores. The number of tasks to be executed is four times the number of processors. Each task must be assigned to a unique core, and each core can only be used once.
//
// You are given an array processorTime representing the time each processor becomes available and an array tasks representing how long each task takes to complete. Return the minimum time needed to complete all tasks.
//
// Example:
// Input: processorTime = [8,10], tasks = [2,2,3,1,8,7,4,5]
//
// Output: 16
//
// Explanation:
//
// Assign the tasks at indices 4, 5, 6, 7 to the first processor which becomes available at time = 8, and the tasks at indices 0, 1, 2, 3 to the second processor which becomes available at time = 10. 
//
// The time taken by the first processor to finish the execution of all tasks is max(8 + 8, 8 + 7, 8 + 4, 8 + 5) = 16.
//
// The time taken by the second processor to finish the execution of all tasks is max(10 + 2, 10 + 2, 10 + 3, 10 + 1) = 13.
//
// Constraints:
// 1 <= n == processorTime.length <= 25000
// 	1 <= tasks.length <= 105
// 	0 <= processorTime[i] <= 109
// 	1 <= tasks[i] <= 109
// 	tasks.length == 4 * n
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minProcessingTime(int* processorTime, int processorTimeSize, int* tasks, int tasksSize) {
    // Sort processorTime in ascending order
    qsort(processorTime, processorTimeSize, sizeof(int), (int (*)(const void *, const void *))strcmp);
    
    // Sort tasks in descending order
    qsort(tasks, tasksSize, sizeof(int), (int (*)(const void *, const void *))strcmp);
    
    int maxTime = 0;
    
    // Assign tasks to processors
    for (int i = 0; i < processorTimeSize; i++) {
        int processorAvailableTime = processorTime[i];
        int taskIndex = i * 4; // Each processor gets 4 tasks
        
        // Calculate the time taken for the current processor to finish its assigned tasks
        int currentProcessorTime = processorAvailableTime + tasks[taskIndex]; // First task
        for (int j = 1; j < 4; j++) {
            currentProcessorTime = currentProcessorTime > (processorAvailableTime + tasks[taskIndex + j]) ? currentProcessorTime : (processorAvailableTime + tasks[taskIndex + j]);
        }
        
        // Update maxTime if the current processor's time is greater
        maxTime = maxTime > currentProcessorTime ? maxTime : currentProcessorTime;
    }
    
    return maxTime;     
}
