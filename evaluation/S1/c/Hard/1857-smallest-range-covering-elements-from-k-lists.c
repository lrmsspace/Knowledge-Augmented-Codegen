// Source: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/   |   Difficulty: Hard
//
// Problem Description:
// You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
//
// We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
//
// Example:
// Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
// Output: [20,24]
// Explanation: 
// List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
// List 2: [0, 9, 12, 20], 20 is in range [20,24].
// List 3: [5, 18, 22, 30], 22 is in range [20,24].
//
// Constraints:
// nums.length == k
// 	1 <= k <= 3500
// 	1 <= nums[i].length <= 50
// 	-105 <= nums[i][j] <= 105
// 	nums[i] is sorted in non-decreasing order.
//
// Helpful references (internal KB):
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
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
int* smallestRange(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    typedef struct {
        int val;
        int row;
        int col;
    } HeapNode;

    typedef struct {
        HeapNode* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(HeapNode* a, HeapNode* b) {
        HeapNode temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent].val <= heap->data[index].val) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void heapifyDown(MinHeap* heap, int index) {
        int left, right, smallest;
        while (1) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;

            if (left < heap->size && heap->data[left].val < heap->data[smallest].val)
                smallest = left;
            if (right < heap->size && heap->data[right].val < heap->data[smallest].val)
                smallest = right;

            if (smallest == index) break;
            swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        }
    }

    void insert(MinHeap* heap, HeapNode node) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size] = node;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    HeapNode extractMin(MinHeap* heap) {
        HeapNode minNode = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapifyDown(heap, 0);
        return minNode;     
    }
    MinHeap* heap = createHeap(numsSize);
    int currentMax = -100000;
    for (int i = 0; i < numsSize; i++) {
        HeapNode node = {nums[i][0], i, 0};
        insert(heap, node);
        if (nums[i][0] > currentMax) {
            currentMax = nums[i][0];
        }
    }   
    int rangeStart = 0, rangeEnd = 100000;
    while (1) {
        HeapNode minNode = extractMin(heap);
        if (currentMax - minNode.val < rangeEnd - rangeStart) {
            rangeStart = minNode.val;
            rangeEnd = currentMax;
        }
        if (minNode.col + 1 == numsColSize[minNode.row]) {
            break; // One list is exhausted
        }
        HeapNode nextNode = {nums[minNode.row][minNode.col + 1], minNode.row, minNode.col + 1};
        insert(heap, nextNode);
        if (nextNode.val > currentMax) {
            currentMax = nextNode.val;
        }
    }
    free(heap->data);
    free(heap);
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = rangeStart;
    result[1] = rangeEnd;
    *returnSize = 2;
    return result;
}
