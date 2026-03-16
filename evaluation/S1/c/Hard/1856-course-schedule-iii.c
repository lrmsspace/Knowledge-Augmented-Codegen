// Source: https://leetcode.com/problems/course-schedule-iii/   |   Difficulty: Hard
//
// Problem Description:
// There are n different online courses numbered from 1 to n. You are given an array courses where courses[i] = [durationi, lastDayi] indicate that the ith course should be taken continuously for durationi days and must be finished before or on lastDayi.
//
// You will start on the 1st day and you cannot take two or more courses simultaneously.
//
// Return the maximum number of courses that you can take.
//
// Example:
// Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
// Output: 3
// Explanation: 
// There are totally 4 courses, but you can take 3 courses at most:
// First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
// Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
// Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
// The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
//
// Constraints:
// 1 <= courses.length <= 104
// 	1 <= durationi, lastDayi <= 104
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
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

int scheduleCourse(int** courses, int coursesSize, int* coursesColSize) {
    /* Min-heap implementation */
    typedef struct MinHeap {
        int *data;
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

    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void minHeapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent] <= heap->data[index]) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void minHeapifyDown(MinHeap* heap, int index) {
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

    void minHeapInsert(MinHeap* heap, int value) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size] = value;
        minHeapifyUp(heap, heap->size);
        heap->size++;
    }

    int minHeapExtractMin(MinHeap* heap) {
        if (heap->size == 0) return -1; // Heap empty
        int minValue = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        minHeapifyDown(heap, 0);
        return minValue;
    }

    // Sort courses by their end days
    int compare(const void* a, const void* b) {
        int* courseA = *(int**)a;
        int* courseB = *(int**)b;
        return courseA[1] - courseB[1];
    }
    qsort(courses, coursesSize, sizeof(int*), compare);
    MinHeap* durationHeap = createMinHeap(coursesSize);
    int currentTime = 0;
    for (int i = 0; i < coursesSize; i++) {
        int duration = courses[i][0];
        int lastDay = courses[i][1];
        if (currentTime + duration <= lastDay) {
            // Take the course
            currentTime += duration;
            minHeapInsert(durationHeap, duration);
        } else if (durationHeap->size > 0 && durationHeap->data[0] > duration) {
            // Replace the longest duration course with the current one
            int longestDuration = minHeapExtractMin(durationHeap);
            currentTime = currentTime - longestDuration + duration;
            minHeapInsert(durationHeap, duration);
        }
    }
    int result = durationHeap->size;
    free(durationHeap->data);
    free(durationHeap);
    return result;
}