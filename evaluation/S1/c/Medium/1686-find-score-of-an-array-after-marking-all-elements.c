// Source: https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Starting with score = 0, apply the following algorithm:
//
//
// 	Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
// 	Add the value of the chosen integer to score.
// 	Mark the chosen element and its two adjacent elements if they exist.
// 	Repeat until all the array elements are marked.
//
//
// Return the score you get after applying the above algorithm.
//
// Example:
// Input: nums = [2,1,3,4,5,2]
// Output: 7
// Explanation: We mark the elements as follows:
// - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
// - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
// - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
// Our score is 1 + 2 + 4 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
//   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
//   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
//   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
//   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long findScore(int* nums, int numsSize) {
    // Min-heap priority queue implementation
    typedef struct {
        int value;
        int index;
    } HeapNode;

    typedef struct {
        HeapNode* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createMinHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(HeapNode* a, HeapNode* b) {
        HeapNode temp = *a;
        *a = *b;
        *b = temp;
    }

    void minHeapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent].value <= heap->data[index].value) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void minHeapifyDown(MinHeap* heap, int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap->size && heap->data[left].value < heap->data[smallest].value)
            smallest = left;
        if (right < heap->size && heap->data[right].value < heap->data[smallest].value)
            smallest = right;

        if (smallest != index) {
            swap(&heap->data[index], &heap->data[smallest]);
            minHeapifyDown(heap, smallest);
        }
    }

    void insertMinHeap(MinHeap* heap, int value, int index) {
        if (heap->size == heap->capacity) return; // Heap is full
        heap->data[heap->size].value = value;
        heap->data[heap->size].index = index;
        heap->size++;
        minHeapifyUp(heap, heap->size - 1);
    }

    HeapNode extractMin(MinHeap* heap) {
        if (heap->size == 0) return (HeapNode){-1, -1}; // Heap is empty
        HeapNode root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        minHeapifyDown(heap, 0);
        return root;
    }
    MinHeap* heap = createMinHeap(numsSize);
    int* marked = (int*)calloc(numsSize, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        insertMinHeap(heap, nums[i], i);
    }
    long long score = 0;
    while (heap->size > 0) {
        HeapNode node = extractMin(heap);
        int idx = node.index;
        if (marked[idx]) continue; // Already marked
        score += node.value;
        marked[idx] = 1;
        if (idx > 0) marked[idx - 1] = 1; // Mark left neighbor
        if (idx < numsSize - 1) marked[idx + 1] = 1; // Mark right neighbor
    }
    free(heap->data);
    free(heap);
    free(marked);
    return score;    
}
