// Source: https://leetcode.com/problems/remove-stones-to-minimize-the-total/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array piles, where piles[i] represents the number of stones in the ith pile, and an integer k. You should apply the following operation exactly k times:
//
//
// 	Choose any piles[i] and remove floor(piles[i] / 2) stones from it.
//
//
// Notice that you can apply the operation on the same pile more than once.
//
// Return the minimum possible total number of stones remaining after applying the k operations.
//
// floor(x) is the largest integer that is smaller than or equal to x (i.e., rounds x down).
//
// Example:
// Input: piles = [5,4,9], k = 2
// Output: 12
// Explanation: Steps of a possible scenario are:
// - Apply the operation on pile 2. The resulting piles are [5,4,5].
// - Apply the operation on pile 0. The resulting piles are [3,4,5].
// The total number of stones in [3,4,5] is 12.
//
// Constraints:
// 1 <= piles.length <= 105
// 	1 <= piles[i] <= 104
// 	1 <= k <= 105
//

int minStoneSum(int* piles, int pilesSize, int k) {
    // Max-heap implementation using an array
    int* heap = (int*)malloc(pilesSize * sizeof(int));
    int heapSize = 0;

    // Function to swap two elements in the heap
    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    // Function to heapify up
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] < heap[index]) {
                swap(&heap[parent], &heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Function to heapify down
    void heapifyDown(int index) {
        while (index < heapSize) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < heapSize && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < heapSize && heap[right] > heap[largest]) {
                largest = right;
            }
            if (largest != index) {
                swap(&heap[index], &heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

    // Build the max-heap
    for (int i = 0; i < pilesSize; i++) {
        heap[heapSize++] = piles[i];
        heapifyUp(heapSize - 1);
    }

    // Perform k operations
    for (int i = 0; i < k; i++) {
        int maxPile = heap[0];
        int stonesToRemove = maxPile / 2;
        heap[0] -= stonesToRemove;
        heapifyDown(0);
    }

    // Calculate the total remaining stones
    int totalStones = 0;
    for (int i = 0; i < heapSize; i++) {
        totalStones += heap[i];
    }

    free(heap);
    return totalStones;     
}
