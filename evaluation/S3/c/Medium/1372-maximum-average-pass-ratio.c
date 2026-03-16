// Source: https://leetcode.com/problems/maximum-average-pass-ratio/   |   Difficulty: Medium
//
// Problem Description:
// There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.
//
// You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.
//
// The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.
//
// Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
// Output: 0.78333
// Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
//
// Constraints:
// 1 <= classes.length <= 105
// 	classes[i].length == 2
// 	1 <= passi <= totali <= 105
// 	1 <= extraStudents <= 105
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    // Define a structure to represent a class with its pass ratio and potential improvement
    typedef struct {
        double passRatio; // Current pass ratio
        double improvement; // Potential improvement if an extra student is added
        int pass; // Number of students passing
        int total; // Total number of students
    } ClassInfo;

    // Create an array to hold class information     
    ClassInfo* classInfos = (ClassInfo*)malloc(classesSize * sizeof(ClassInfo));
    for (int i = 0; i < classesSize; i++) {
        int pass = classes[i][0];
        int total = classes[i][1];
        classInfos[i].pass = pass;
        classInfos[i].total = total;
        classInfos[i].passRatio = (double)pass / total;
        classInfos[i].improvement = ((double)(pass + 1) / (total + 1)) - classInfos[i].passRatio;
    }
    
    // Use a max-heap to store classes based on their potential improvement
    for (int i = 0; i < extraStudents; i++) {
        // Find the class with the maximum improvement
        int maxIndex = 0;
        for (int j = 1; j < classesSize; j++) {
            if (classInfos[j].improvement > classInfos[maxIndex].improvement) {
                maxIndex = j;
            }
        }
        
        // Add an extra student to the class with the maximum improvement
        classInfos[maxIndex].pass++;
        classInfos[maxIndex].total++;
        classInfos[maxIndex].passRatio = (double)classInfos[maxIndex].pass / classInfos[maxIndex].total;
        classInfos[maxIndex].improvement = ((double)(classInfos[maxIndex].pass + 1) / (classInfos[maxIndex].total + 1)) - classInfos[maxIndex].passRatio;
    }
    
    // Calculate the final average pass ratio
    double totalRatio = 0.0;
    for (int i = 0; i < classesSize; i++) {
        totalRatio += classInfos[i].passRatio;
    }
    double averageRatio = totalRatio / classesSize;
    
    // Free allocated memory
    free(classInfos);
    
    return averageRatio;
}
