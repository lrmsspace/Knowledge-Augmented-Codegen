// Source: https://leetcode.com/problems/maximum-performance-of-a-team/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and k and two integer arrays speed and efficiency both of length n. There are n engineers numbered from 1 to n. speed[i] and efficiency[i] represent the speed and efficiency of the ith engineer respectively.
//
// Choose at most k different engineers out of the n engineers to form a team with the maximum performance.
//
// The performance of a team is the sum of its engineers' speeds multiplied by the minimum efficiency among its engineers.
//
// Return the maximum performance of this team. Since the answer can be a huge number, return it modulo 109 + 7.
//
// Example:
// Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
// Output: 60
// Explanation: 
// We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
//
// Constraints:
// 1 <= k <= n <= 105
// 	speed.length == n
// 	efficiency.length == n
// 	1 <= speed[i] <= 105
// 	1 <= efficiency[i] <= 108
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
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

int maxPerformance(int n, int* speed, int speedSize, int* efficiency, int efficiencySize, int k) {
    // Pair efficiency and speed
    typedef struct Engineer {
        int efficiency;
        int speed;
    } Engineer;

    Engineer* engineers = (Engineer*)malloc(n * sizeof(Engineer));
    for (int i = 0; i < n; i++) {
        engineers[i].efficiency = efficiency[i];
        engineers[i].speed = speed[i];
    }

    // Sort engineers by efficiency in descending order
    int cmp(const void* a, const void* b) {
        return ((Engineer*)b)->efficiency - ((Engineer*)a)->efficiency;
    }
    qsort(engineers, n, sizeof(Engineer), cmp);

    // Min-heap for speeds
    typedef struct MinHeap {
        int* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createMinHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (int*)malloc(capacity * sizeof(int));
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void minHeapPush(MinHeap* heap, int val) {
        if (heap->size < heap->capacity) {
            heap->data[heap->size++] = val;
            int idx = heap->size - 1;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (heap->data[parent] > heap->data[idx]) {
                    int temp = heap->data[parent];
                    heap->data[parent] = heap->data[idx];
                    heap->data[idx] = temp;
                    idx = parent;
                } else {
                    break;
                }
            }
        } else if (val > heap->data[0]) {
            heap->data[0] = val;
            int idx = 0;
            while (1) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int smallest = idx;
                if (left < heap->size && heap->data[left] < heap->data[smallest]) {
                    smallest = left;
                }
                if (right < heap->size && heap->data[right] < heap->data[smallest]) {
                    smallest = right;
                }
                if (smallest != idx) {
                    int temp = heap->data[smallest];
                    heap->data[smallest] = heap->data[idx];
                    heap->data[idx] = temp;
                    idx = smallest;
                } else {
                    break;
                }
            }
        }
    }
    int minHeapPop(MinHeap* heap) {
        if (heap->size == 0) return 0;
        int root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int idx = 0;
        while (1) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;
            if (left < heap->size && heap->data[left] < heap->data[smallest]) {
                smallest = left;
            }
            if (right < heap->size && heap->data[right] < heap->data[smallest]) {
                smallest = right;
            }
            if (smallest != idx) {
                int temp = heap->data[smallest];
                heap->data[smallest] = heap->data[idx];
                heap->data[idx] = temp;
                idx = smallest;
            } else {
                break;
            }
        }
        return root;
    }
    MinHeap* speedHeap = createMinHeap(k);
    long long speedSum = 0;
    long long maxPerf = 0;
    const int MOD = 1000000007;
    for (int i = 0; i < n; i++) {
        Engineer eng = engineers[i];
        minHeapPush(speedHeap, eng.speed);
        speedSum += eng.speed;
        if (speedHeap->size > k) {
            speedSum -= minHeapPop(speedHeap);
        }
        long long perf = speedSum * eng.efficiency;
        if (perf > maxPerf) {
            maxPerf = perf;
        }
    }
    free(engineers);
    free(speedHeap->data);
    free(speedHeap);
    return (int)(maxPerf % MOD);
}
