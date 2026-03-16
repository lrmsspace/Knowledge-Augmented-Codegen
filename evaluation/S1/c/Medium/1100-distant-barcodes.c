// Source: https://leetcode.com/problems/distant-barcodes/   |   Difficulty: Medium
//
// Problem Description:
// In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
//
// Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.
//
// Example:
// Input: barcodes = [1,1,1,2,2,2]
// Output: [2,1,2,1,2,1]
//
// Constraints:
// 1 <= barcodes.length <= 10000
// 	1 <= barcodes[i] <= 10000
//
// Helpful references (internal KB):
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
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
int* rearrangeBarcodes(int* barcodes, int barcodesSize, int* returnSize) {
    int freq[10001] = {0};
    for (int i = 0; i < barcodesSize; ++i) {
        freq[barcodes[i]]++;
    }

    // Max-heap implementation using an array
    typedef struct {
        int value;
        int count;
    } HeapNode;

    HeapNode heap[10001];
    int heapSize = 0;

    // Build the max-heap
    for (int i = 0; i <= 10000; ++i) {
        if (freq[i] > 0) {
            heap[heapSize].value = i;
            heap[heapSize].count = freq[i];
            heapSize++;
        }
    }

    // Heapify function
    void heapify(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heapSize && heap[left].count > heap[largest].count) {
            largest = left;
        }
        if (right < heapSize && heap[right].count > heap[largest].count) {
            largest = right;
        }
        if (largest != index) {
            HeapNode temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            heapify(largest);
        }
    }

    // Build the initial max-heap
    for (int i = (heapSize / 2) - 1; i >= 0; --i) {
        heapify(i);
    }

    int* result = (int*)malloc(barcodesSize * sizeof(int));
    int idx = 0;

    while (heapSize > 1) {
        // Extract the two most frequent elements
        HeapNode first = heap[0];
        heap[0] = heap[--heapSize];
        heapify(0);

        HeapNode second = heap[0];
        heap[0] = heap[--heapSize];
        heapify(0);

        // Place them in the result array
        result[idx++] = first.value;
        result[idx++] = second.value;

        // Decrease their counts and reinsert if they are still available
        if (--first.count > 0) {
            heap[heapSize] = first;
            heapSize++;
            int i = heapSize - 1;
            while (i > 0 && heap[(i - 1) / 2].count < heap[i].count) {
                HeapNode temp = heap[i];
                heap[i] = heap[(i - 1) / 2];
                heap[(i - 1) / 2] = temp;
                i = (i - 1) / 2;
            }
        }
        if (--second.count > 0) {
            heap[heapSize] = second;
            heapSize++;
            int i = heapSize - 1;
            while (i > 0 && heap[(i - 1) / 2].count < heap[i].count) {
                HeapNode temp = heap[i];
                heap[i] = heap[(i - 1) / 2];
                heap[(i - 1) / 2] = temp;
                i = (i - 1) / 2;
            }
        }
    }
    // If there's one element left, place it at the end
    if (heapSize == 1) {
        result[idx++] = heap[0].value;
    }
    *returnSize = barcodesSize;
    return result;
}
