// Source: https://leetcode.com/problems/minimize-deviation-in-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers.
//
// You can perform two types of operations on any element of the array any number of times:
//
//
// 	If the element is even, divide it by 2.
//
// 	
// 		For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
// 	
// 	
// 	If the element is odd, multiply it by 2.
// 	
// 		For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
// 	
// 	
//
//
// The deviation of the array is the maximum difference between any two elements in the array.
//
// Return the minimum deviation the array can have after performing some number of operations.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 1
// Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 5 * 104
// 	1 <= nums[i] <= 109
//

int minimumDeviation(int* nums, int numsSize) {
    #include <limits.h>
    #include <stdbool.h>
    #include <stdlib.h>

    typedef struct {
        int* data;
        int size;
        int capacity;
    } MaxHeap;

    MaxHeap* createHeap(int capacity) {
        MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
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

    void heapifyUp(MaxHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent] < heap->data[index]) {
                swap(&heap->data[parent], &heap->data[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(MaxHeap* heap, int index) {
        while (2 * index + 1 < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < heap->size && heap->data[left] > heap->data[largest]) {
                largest = left;
            }
            if (right < heap->size && heap->data[right] > heap->data[largest]) {
                largest = right;
            }
            if (largest != index) {
                swap(&heap->data[largest], &heap->data[index]);
                index = largest;
            } else {
                break;
            }
        }
    }

    void insert(MaxHeap* heap, int value) {
        if (heap->size == heap->capacity) return; // Heap is full
        heap->data[heap->size] = value;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    int extractMax(MaxHeap* heap) {
        if (heap->size == 0) return INT_MIN; // Heap is empty
        int maxVal = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapifyDown(heap, 0);
        return maxVal;
    }
    MaxHeap* heap = createHeap(numsSize);
    int minVal = INT_MAX;
    for (int i = 0; i < numsSize; i++) {
        int val = nums[i];
        if (val % 2 == 1) {
            val *= 2; // Make odd numbers even
        }
        insert(heap, val);
        if (val < minVal) {
            minVal = val;
        }
    }
    int minDeviation = INT_MAX;
    while (true) {
        int maxVal = extractMax(heap);
        minDeviation = (maxVal - minVal < minDeviation) ? maxVal - minVal : minDeviation;
        if (maxVal % 2 == 0) {
            maxVal /= 2;
            if (maxVal < minVal) {
                minVal = maxVal;
            }
            insert(heap, maxVal);
        } else {
            break; // Max value is odd, cannot reduce further
        }
    }
    return minDeviation;
}
