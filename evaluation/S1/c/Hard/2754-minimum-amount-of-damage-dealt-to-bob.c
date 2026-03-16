// Source: https://leetcode.com/problems/minimum-amount-of-damage-dealt-to-bob/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer power and two integer arrays damage and health, both having length n.
//
// Bob has n enemies, where enemy i will deal Bob damage[i] points of damage per second while they are alive (i.e. health[i] > 0).
//
// Every second, after the enemies deal damage to Bob, he chooses one of the enemies that is still alive and deals power points of damage to them.
//
// Determine the minimum total amount of damage points that will be dealt to Bob before all n enemies are dead.
//
// Example:
// Input: power = 4, damage = [1,2,3,4], health = [4,5,6,8]
//
// Output: 39
//
// Explanation:
//
//
// 	Attack enemy 3 in the first two seconds, after which enemy 3 will go down, the number of damage points dealt to Bob is 10 + 10 = 20 points.
// 	Attack enemy 2 in the next two seconds, after which enemy 2 will go down, the number of damage points dealt to Bob is 6 + 6 = 12 points.
// 	Attack enemy 0 in the next second, after which enemy 0 will go down, the number of damage points dealt to Bob is 3 points.
// 	Attack enemy 1 in the next two seconds, after which enemy 1 will go down, the number of damage points dealt to Bob is 2 + 2 = 4 points.
//
// Constraints:
// 1 <= power <= 104
// 	1 <= n == damage.length == health.length <= 105
// 	1 <= damage[i], health[i] <= 104
//
// Helpful references (internal KB):
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
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

long long minDamage(int power, int* damage, int damageSize, int* health, int healthSize) {
    typedef struct Job {
        int deadline;
        int runTime;
    } Job;

    int n = damageSize;
    Job* jobs = (Job*)malloc(n * sizeof(Job));
    if (!jobs) return -1; /* allocation failure */

    for (int i = 0; i < n; ++i) {
        jobs[i].deadline = (health[i] + power - 1) / power; /* ceiling division */
        jobs[i].runTime = damage[i];
    }

    /* Sort jobs by deadline descending, then by runTime ascending */
    int cmpJobs(const void* a, const void* b) {
        Job* jobA = (Job*)a;
        Job* jobB = (Job*)b;
        if (jobA->deadline != jobB->deadline)
            return jobB->deadline - jobA->deadline; /* descending deadline */
        return jobA->runTime - jobB->runTime; /* ascending runTime */
    }
    qsort(jobs, n, sizeof(Job), cmpJobs);

    /* Min-heap for runTimes */
    typedef struct MinHeap {
        int* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        if (!heap) return NULL;
        heap->data = (int*)malloc(capacity * sizeof(int));
        if (!heap->data) { free(heap); return NULL; }
        heap->size = 0; heap->capacity = capacity;
        return heap;
    }

    void freeHeap(MinHeap* heap) {
        if (heap) {
            free(heap->data);
            free(heap);
        }
    }

    int heapPush(MinHeap* heap, int val) {
        if (heap->size >= heap->capacity) return -1; /* overflow */
        int i = heap->size++;
        heap->data[i] = val;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap->data[parent] <= heap->data[i]) break;
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[i];
            heap->data[i] = temp;
            i = parent;
        }
        return 0;
    }       
    int heapPop(MinHeap* heap) {
        if (heap->size == 0) return -1; /* underflow */
        int ret = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int i = 0;
        while (1) {
            int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
            if (left < heap->size && heap->data[left] < heap->data[smallest])
                smallest = left;
            if (right < heap->size && heap->data[right] < heap->data[smallest])
                smallest = right;
            if (smallest == i) break;
            int temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp;
            i = smallest;
        }
        return ret;
    }
    MinHeap* heap = createHeap(n);
    if (!heap) {
        free(jobs);
        return -1; /* allocation failure */
    }
    long long totalDamage = 0;
    int currentTime = 0;
    for (int i = 0; i < n; ++i) {
        int deadline = jobs[i].deadline;
        int runTime = jobs[i].runTime;

        while (currentTime < deadline) {
            if (heap->size == 0) break;
            int rt = heapPop(heap);
            totalDamage += (long long)rt * (deadline - currentTime);
            currentTime++;
        }
        heapPush(heap, runTime);
    }
    while (heap->size > 0) {
        int rt = heapPop(heap);
        totalDamage += (long long)rt * (currentTime + 1);
        currentTime++;
    }
    freeHeap(heap);
    free(jobs);
    return totalDamage;
}
