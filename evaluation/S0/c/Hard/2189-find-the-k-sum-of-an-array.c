// Source: https://leetcode.com/problems/find-the-k-sum-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. You can choose any subsequence of the array and sum all of its elements together.
//
// We define the K-Sum of the array as the kth largest subsequence sum that can be obtained (not necessarily distinct).
//
// Return the K-Sum of the array.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Note that the empty subsequence is considered to have a sum of 0.
//
// Example:
// Input: nums = [2,4,-2], k = 5
// Output: 2
// Explanation: All the possible subsequence sums that we can obtain are the following sorted in decreasing order:
// 6, 4, 4, 2, 2, 0, 0, -2.
// The 5-Sum of the array is 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= k <= min(2000, 2n)
//

long long kSum(int* nums, int numsSize, int k) {
    /* Max-heap implementation */
    typedef struct {
        long long *data;
        int size;
        int capacity;
    } MaxHeap;

    MaxHeap* createHeap(int capacity) {
        MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
        heap->data = (long long*)malloc(sizeof(long long) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void freeHeap(MaxHeap *heap) {
        free(heap->data);
        free(heap);
    }

    void swap(long long *a, long long *b) {
        long long temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(MaxHeap *heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent] >= heap->data[index]) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void heapifyDown(MaxHeap *heap, int index) {
        int left, right, largest;
        while (1) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            largest = index;

            if (left < heap->size && heap->data[left] > heap->data[largest])
                largest = left;
            if (right < heap->size && heap->data[right] > heap->data[largest])
                largest = right;

            if (largest == index) break;
            swap(&heap->data[index], &heap->data[largest]);
            index = largest;
        }
    }

    void push(MaxHeap *heap, long long value) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size++] = value;
        heapifyUp(heap, heap->size - 1);
    }

    long long pop(MaxHeap *heap) {
        if (heap->size == 0) return 0; // Heap empty
        long long top = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return top;
    }

    /* Main logic      
    */
    long long totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            totalSum += nums[i];
            nums[i] = -nums[i];
        }
    }
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    MaxHeap *heap = createHeap(k);
    push(heap, 0);
    long long result = totalSum;
    for (int i = 0; i < k - 1; i++) {
        long long curr = pop(heap);
        if (curr == LLONG_MIN) break;
        result = totalSum + curr;
        for (int j = 0; j < numsSize; j++) {
            long long next = curr + nums[j];
            push(heap, next);
            if (curr - nums[j] == next) break; // Avoid duplicates
        }
    }
    freeHeap(heap);
    return result; 
}
