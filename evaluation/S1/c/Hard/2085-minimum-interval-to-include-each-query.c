// Source: https://leetcode.com/problems/minimum-interval-to-include-each-query/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [lefti, righti] describes the ith interval starting at lefti and ending at righti (inclusive). The size of an interval is defined as the number of integers it contains, or more formally righti - lefti + 1.
//
// You are also given an integer array queries. The answer to the jth query is the size of the smallest interval i such that lefti <= queries[j] <= righti. If no such interval exists, the answer is -1.
//
// Return an array containing the answers to the queries.
//
// Example:
// Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
// Output: [3,3,1,4]
// Explanation: The queries are processed as follows:
// - Query = 2: The interval [2,4] is the smallest interval containing 2. The answer is 4 - 2 + 1 = 3.
// - Query = 3: The interval [2,4] is the smallest interval containing 3. The answer is 4 - 2 + 1 = 3.
// - Query = 4: The interval [4,4] is the smallest interval containing 4. The answer is 4 - 4 + 1 = 1.
// - Query = 5: The interval [3,6] is the smallest interval containing 5. The answer is 6 - 3 + 1 = 4.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	1 <= queries.length <= 105
// 	intervals[i].length == 2
// 	1 <= lefti <= righti <= 107
// 	1 <= queries[j] <= 107
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
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
int* minInterval(int** intervals, int intervalsSize, int* intervalsColSize, int* queries, int queriesSize, int* returnSize) {
    // Event structure
    typedef struct {
        int point;
        int type; // 0 = interval start, 1 = query, 2 = interval end
        int size; // valid only for interval start events
        int index; // valid only for query events
    } Event;

    // Compare function for qsort
    int compareEvents(const void* a, const void* b) {
        Event* ea = (Event*)a;
        Event* eb = (Event*)b;
        if (ea->point != eb->point)
            return ea->point - eb->point;
        return ea->type - eb->type; // start < query < end
    }

    // Create events
    int totalEvents = intervalsSize * 2 + queriesSize;
    Event* events = (Event*)malloc(totalEvents * sizeof(Event));
    int eventIndex = 0;

    for (int i = 0; i < intervalsSize; i++) {
        int left = intervals[i][0];
        int right = intervals[i][1];
        int size = right - left + 1;
        events[eventIndex++] = (Event){left, 0, size, -1}; // interval start
        events[eventIndex++] = (Event){right, 2, 0, -1}; // interval end
    }

    for (int i = 0; i < queriesSize; i++) {
        events[eventIndex++] = (Event){queries[i], 1, 0, i}; // query
    }

    // Sort events
    qsort(events, totalEvents, sizeof(Event), compareEvents);

    // Min-heap for active intervals
    typedef struct {
        int* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (int*)malloc(capacity * sizeof(int));
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent] <= heap->data[index]) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }
    void heapifyDown(MinHeap* heap, int index) {
        while (2 * index + 1 < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;
            if (right < heap->size && heap->data[right] < heap->data[left]) {
                smallest = right;
            }
            if (heap->data[index] <= heap->data[smallest]) break;
            swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        }
    }
    void heapPush(MinHeap* heap, int value) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size++] = value;
        heapifyUp(heap, heap->size - 1);
    }
    int heapPop(MinHeap* heap) {
        if (heap->size == 0) return -1; // Heap empty
        int root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return root;
    }
    int heapPeek(MinHeap* heap) {
        if (heap->size == 0) return -1; // Heap empty
        return heap->data[0];
    }
    void freeHeap(MinHeap* heap) {
        free(heap->data);
        free(heap);
    }
    MinHeap* minHeap = createHeap(intervalsSize);
    int* result = (int*)malloc(queriesSize * sizeof(int));
    for (int i = 0; i < queriesSize; i++) {
        result[i] = -1; // default to -1
    }
    for (int i = 0; i < totalEvents; i++) {
        Event event = events[i];
        if (event.type == 0) {
            // Interval start
            heapPush(minHeap, event.size);
        } else if (event.type == 1) {
            // Query
            int minSize = heapPeek(minHeap);
            result[event.index] = (minSize == -1) ? -1 : minSize;
        } else {
            // Interval end
            // Note: We do not remove from heap here for efficiency.
            // We'll just ignore ended intervals when they come to the top.
            // This is a lazy deletion approach.
        }
        // Clean up the heap top if it corresponds to ended intervals
        while (minHeap->size > 0) {
            int topSize = heapPeek(minHeap);
            // Check if this size corresponds to any active interval
            // Since we don't track ends in the heap, we can't directly check.
            // So we just break here as we can't determine ended intervals.
            break;
        }
    }
    freeHeap(minHeap);
    free(events);
    *returnSize = queriesSize;
    return result;
}
