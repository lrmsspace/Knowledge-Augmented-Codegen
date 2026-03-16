// Source: https://leetcode.com/problems/minimum-cost-to-hire-k-workers/   |   Difficulty: Hard
//
// Problem Description:
// There are n workers. You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.
//
// We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay them according to the following rules:
//
//
// 	Every worker in the paid group must be paid at least their minimum wage expectation.
// 	In the group, each worker's pay must be directly proportional to their quality. This means if a worker’s quality is double that of another worker in the group, then they must be paid twice as much as the other worker.
//
//
// Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: quality = [10,20,5], wage = [70,50,30], k = 2
// Output: 105.00000
// Explanation: We pay 70 to 0th worker and 35 to 2nd worker.
//
// Constraints:
// n == quality.length == wage.length
// 	1 <= k <= n <= 104
// 	1 <= quality[i], wage[i] <= 104
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int wageSize, int k) {
    typedef struct Worker {
        int quality;
        int wage;
        double ratio; /* wage / quality */
    } Worker;

    int cmpWorker(const void *a, const void *b) {
        double r1 = ((Worker*)a)->ratio;
        double r2 = ((Worker*)b)->ratio;
        if (r1 < r2) return -1;
        else if (r1 > r2) return 1;
        else return 0;
    }

    Worker *workers = (Worker*)malloc(qualitySize * sizeof(Worker));
    for (int i = 0; i < qualitySize; ++i) {
        workers[i].quality = quality[i];
        workers[i].wage = wage[i];
        workers[i].ratio = (double)wage[i] / quality[i];
    }
    qsort(workers, qualitySize, sizeof(Worker), cmpWorker);

    /* Max-heap for qualities */
    int *heap = (int*)malloc(k * sizeof(int));
    int heapSize = 0;
    #define HEAP_PUSH(x) do { \
        heap[heapSize++] = (x); \
        int idx = heapSize - 1; \
        while (idx > 0) { \
            int parent = (idx - 1) / 2; \
            if (heap[parent] >= heap[idx]) break; \
            int tmp = heap[parent]; heap[parent] = heap[idx]; heap[idx] = tmp; \
            idx = parent; \
        } \
    } while(0)
    #define HEAP_POP() do { \
        heap[0] = heap[--heapSize]; \
        int idx = 0; \
        while (1) { \
            int left = idx * 2 + 1; \
            int right = idx * 2 + 2; \
            int largest = idx; \
            if (left < heapSize && heap[left] > heap[largest]) largest = left; \
            if (right < heapSize && heap[right] > heap[largest]) largest = right; \
            if (largest == idx) break; \
            int tmp = heap[largest]; heap[largest] = heap[idx]; heap[idx] = tmp; \
            idx = largest; \
        } \
    } while(0)

    double minCost = 1e20;
    int totalQuality = 0;
    for (int i = 0; i < qualitySize; ++i) {
        HEAP_PUSH(workers[i].quality);
        totalQuality += workers[i].quality;

        if (heapSize > k) {
            totalQuality -= heap[0];
            HEAP_POP();
        }

        if (heapSize == k) {
            double cost = totalQuality * workers[i].ratio;
            if (cost < minCost) {
                minCost = cost;
            }
        }
    }
    free(workers);
    free(heap);
    return minCost;
}
