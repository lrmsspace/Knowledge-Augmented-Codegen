// Source: https://leetcode.com/problems/kth-largest-element-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the kth largest element in the array.
//
// Note that it is the kth largest element in the sorted order, not the kth distinct element.
//
// Can you solve it without sorting?
//
// Example:
// Input: nums = [3,2,1,5,6,4], k = 2
// Output: 5
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

int findKthLargest(int* nums, int numsSize, int k) {
    // Min-heap implementation
    int *heap = (int *)malloc(k * sizeof(int));
    int heapSize = 0;

    // Helper functions for heap operations
    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] > heap[index]) {
                swap(&heap[parent], &heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        while (index < heapSize) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < heapSize && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < heapSize && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                swap(&heap[smallest], &heap[index]);
                index = smallest;
            } else {
                break;
            }
        }
    }

    // Build the min-heap with the first k elements
    for (int i = 0; i < numsSize; i++) {
        if (heapSize < k) {
            heap[heapSize++] = nums[i];
            heapifyUp(heapSize - 1);
        } else if (nums[i] > heap[0]) {
            heap[0] = nums[i];
            heapifyDown(0);
        }
    }

    int kthLargest = heap[0];
    free(heap);
    return kthLargest;      
}
