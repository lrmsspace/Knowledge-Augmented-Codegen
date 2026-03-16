// Source: https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums, and an integer k.
//
// You are allowed to perform some operations on nums, where in a single operation, you can:
//
//
// 	Select the two smallest integers x and y from nums.
// 	Remove x and y from nums.
// 	Insert (min(x, y) * 2 + max(x, y)) at any position in the array.
//
//
// Note that you can only apply the described operation if nums contains at least two elements.
//
// Return the minimum number of operations needed so that all elements of the array are greater than or equal to k.
//
// Example:
// Input: nums = [2,11,10,1,3], k = 10
//
// Output: 2
//
// Explanation:
//
//
// 	In the first operation, we remove elements 1 and 2, then add 1 * 2 + 2 to nums. nums becomes equal to [4, 11, 10, 3].
// 	In the second operation, we remove elements 3 and 4, then add 3 * 2 + 4 to nums. nums becomes equal to [10, 11, 10].
//
//
// At this stage, all the elements of nums are greater than or equal to 10 so we can stop. 
//
// It can be shown that 2 is the minimum number of operations needed so that all elements of the array are greater than or equal to 10.
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
// 	The input is generated such that an answer always exists. That is, after performing some number of operations, all elements of the array are greater than or equal to k.
//

int minOperations(int* nums, int numsSize, int k) {
    // Min-heap implementation
    typedef struct {
        int *data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (int*)malloc(sizeof(int) * capacity);
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
            if (heap->data[parent] > heap->data[index]) {
                swap(&heap->data[parent], &heap->data[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(MinHeap* heap, int index) {
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
            heapifyDown(heap, smallest);
        }
    }

    void insert(MinHeap* heap, int value) {
        if (heap->size == heap->capacity) return; // Heap is full
        heap->data[heap->size] = value;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    int extractMin(MinHeap* heap) {
        if (heap->size == 0) return -1; // Heap is empty
        int minValue = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapifyDown(heap, 0);
        return minValue;
    }

    // Create and populate the min-heap
    MinHeap* heap = createHeap(numsSize);
    for (int i = 0; i < numsSize; i++) {
        insert(heap, nums[i]);
    }
    int operations = 0;
    while (heap->size > 0 && heap->data[0] < k) {
        if (heap->size < 2) {
            return -1; // Not enough elements to perform operation
        }
        int x = extractMin(heap);
        int y = extractMin(heap);
        int newElement = (x < y ? x * 2 + y : y * 2 + x);
        insert(heap, newElement);
        operations++;
    }
    return operations;
}
