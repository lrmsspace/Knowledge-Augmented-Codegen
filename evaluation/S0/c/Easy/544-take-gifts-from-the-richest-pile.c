// Source: https://leetcode.com/problems/take-gifts-from-the-richest-pile/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:
//
//
// 	Choose the pile with the maximum number of gifts.
// 	If there is more than one pile with the maximum number of gifts, choose any.
// 	Reduce the number of gifts in the pile to the floor of the square root of the original number of gifts in the pile.
//
//
// Return the number of gifts remaining after k seconds.
//
// Example:
// Input: gifts = [25,64,9,4,100], k = 4
// Output: 29
// Explanation: 
// The gifts are taken in the following way:
// - In the first second, the last pile is chosen and 10 gifts are left behind.
// - Then the second pile is chosen and 8 gifts are left behind.
// - After that the first pile is chosen and 5 gifts are left behind.
// - Finally, the last pile is chosen again and 3 gifts are left behind.
// The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.
//
// Constraints:
// 1 <= gifts.length <= 103
// 	1 <= gifts[i] <= 109
// 	1 <= k <= 103
//

long long pickGifts(int* gifts, int giftsSize, int k) {
    // Max-heap implementation using an array
    int heap[giftsSize];
    int heapSize = 0;

    // Function to swap two elements
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
    for (int i = 0; i < giftsSize; i++) {
        heap[heapSize++] = gifts[i];
        heapifyUp(heapSize - 1);
    }

    // Perform k operations
    for (int i = 0; i < k; i++) {
        if (heapSize == 0) break;

        int maxGift = heap[0];
        int newGiftCount = (int)sqrt(maxGift);

        // Replace the root with the new gift count and heapify down
        heap[0] = newGiftCount;
        heapifyDown(0);
    }

    // Calculate the total remaining gifts
    long long totalGifts = 0;
    for (int i = 0; i < heapSize; i++) {
        totalGifts += heap[i];
    }

    return totalGifts;      
}
