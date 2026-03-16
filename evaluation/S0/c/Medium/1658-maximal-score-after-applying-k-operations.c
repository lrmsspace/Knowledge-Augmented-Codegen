// Source: https://leetcode.com/problems/maximal-score-after-applying-k-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.
//
// In one operation:
//
//
// 	choose an index i such that 0 <= i < nums.length,
// 	increase your score by nums[i], and
// 	replace nums[i] with ceil(nums[i] / 3).
//
//
// Return the maximum possible score you can attain after applying exactly k operations.
//
// The ceiling function ceil(val) is the least integer greater than or equal to val.
//
// Example:
// Input: nums = [10,10,10,10,10], k = 5
// Output: 50
// Explanation: Apply the operation to each array element exactly once. The final score is 10 + 10 + 10 + 10 + 10 = 50.
//
// Constraints:
// 1 <= nums.length, k <= 105
// 	1 <= nums[i] <= 109
//

long long maxKelements(int* nums, int numsSize, int k) {
    // Max-Heap Implementation
    typedef struct {
        int *data;
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
        int left, right, largest;
        while (index < heap->size) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            largest = index;

            if (left < heap->size && heap->data[left] > heap->data[largest]) {
                largest = left;
            }
            if (right < heap->size && heap->data[right] > heap->data[largest]) {
                largest = right;
            }
            if (largest != index) {
                swap(&heap->data[index], &heap->data[largest]);
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
        if (heap->size == 0) return -1; // Heap is empty
        int maxVal = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return maxVal;
    }
    MaxHeap* heap = createHeap(numsSize);
    for (int i = 0; i < numsSize; i++) {
        insert(heap, nums[i]);
    }
    long long score = 0;
    for (int i = 0; i < k; i++) {
        int maxVal = extractMax(heap);
        score += maxVal;
        int newVal = (maxVal + 2) / 3; // ceil division by 3
        insert(heap, newVal);
    }
    free(heap->data);
    free(heap);
    return score;
    
}
