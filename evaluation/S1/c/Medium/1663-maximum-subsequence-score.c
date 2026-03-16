// Source: https://leetcode.com/problems/maximum-subsequence-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of equal length n and a positive integer k. You must choose a subsequence of indices from nums1 of length k.
//
// For chosen indices i0, i1, ..., ik - 1, your score is defined as:
//
//
// 	The sum of the selected elements from nums1 multiplied with the minimum of the selected elements from nums2.
// 	It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).
//
//
// Return the maximum possible score.
//
// A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1} by deleting some or no elements.
//
// Example:
// Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
// Output: 12
// Explanation: 
// The four possible subsequence scores are:
// - We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3) = 7.
// - We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4) = 6. 
// - We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4) = 12. 
// - We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4) = 8.
// Therefore, we return the max score, which is 12.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	0 <= nums1[i], nums2[j] <= 105
// 	1 <= k <= n
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maxScore(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    // Pair nums2 and nums1 together and sort by nums2 in descending order
    typedef struct {
        int num1;
        int num2;
    } Pair;

    int compare(const void* a, const void* b) {
        Pair* pairA = (Pair*)a;
        Pair* pairB = (Pair*)b;
        return pairB->num2 - pairA->num2; // Descending order
    }

    Pair* pairs = (Pair*)malloc(nums1Size * sizeof(Pair));
    for (int i = 0; i < nums1Size; i++) {
        pairs[i].num1 = nums1[i];
        pairs[i].num2 = nums2[i];
    }

    qsort(pairs, nums1Size, sizeof(Pair), compare);

    // Use a min-heap to keep track of the k largest nums1 values
    typedef struct {
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

    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void minHeapify(MinHeap* heap, int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest != index) {
            swap(&heap->data[index], &heap->data[smallest]);
            minHeapify(heap, smallest);
        }
    }
    void insertMinHeap(MinHeap* heap, int value) {
        if (heap->size == heap->capacity) {
            if (value <= heap->data[0]) {
                return; // No need to insert
            }
            heap->data[0] = value;
            minHeapify(heap, 0);
        } else {
            heap->data[heap->size++] = value;
            int index = heap->size - 1;
            while (index != 0 && heap->data[(index - 1) / 2] > heap->data[index]) {
                swap(&heap->data[index], &heap->data[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
        }
    }
    int extractMin(MinHeap* heap) {
        if (heap->size == 0) return -1; // Heap is empty
        int root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        minHeapify(heap, 0);
        return root;
    }
    MinHeap* heap = createMinHeap(k);
    long long sumNums1 = 0;
    long long maxScore = 0;
    for (int i = 0; i < nums1Size; i++) {
        insertMinHeap(heap, pairs[i].num1);
        sumNums1 += pairs[i].num1;

        if (heap->size > k) {
            int removed = extractMin(heap);
            sumNums1 -= removed;
        }

        if (heap->size == k) {
            long long currentScore = sumNums1 * pairs[i].num2;
            if (currentScore > maxScore) {
                maxScore = currentScore;
            }
        }
    }
    free(pairs);
    free(heap->data);
    free(heap);
    return maxScore;
}
