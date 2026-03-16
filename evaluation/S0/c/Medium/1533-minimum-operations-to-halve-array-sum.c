// Source: https://leetcode.com/problems/minimum-operations-to-halve-array-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of positive integers. In one operation, you can choose any number from nums and reduce it to exactly half the number. (Note that you may choose this reduced number in future operations.)
//
// Return the minimum number of operations to reduce the sum of nums by at least half.
//
// Example:
// Input: nums = [5,19,8,1]
// Output: 3
// Explanation: The initial sum of nums is equal to 5 + 19 + 8 + 1 = 33.
// The following is one of the ways to reduce the sum by at least half:
// Pick the number 19 and reduce it to 9.5.
// Pick the number 9.5 and reduce it to 4.75.
// Pick the number 8 and reduce it to 4.
// The final array is [5, 4.75, 4, 1] with a total sum of 5 + 4.75 + 4 + 1 = 14.75. 
// The sum of nums has been reduced by 33 - 14.75 = 18.25, which is at least half of the initial sum, 18.25 >= 33/2 = 16.5.
// Overall, 3 operations were used so we return 3.
// It can be shown that we cannot reduce the sum by at least half in less than 3 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 107
//

int halveArray(int* nums, int numsSize) {
    // Max-heap implementation using an array
    double* heap = (double*)malloc(numsSize * sizeof(double));
    int heapSize = 0;

    // Function to swap two elements in the heap
    void swap(int i, int j) {
        double temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // Function to maintain the max-heap property
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] < heap[index]) {
                swap(parent, index);
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
            int largest = index;

            if (left < heapSize && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < heapSize && heap[right] > heap[largest]) {
                largest = right;
            }
            if (largest != index) {
                swap(largest, index);
                index = largest;
            } else {
                break;
            }
        }
    }

    // Insert elements into the max-heap
    double totalSum = 0.0;
    for (int i = 0; i < numsSize; i++) {
        heap[heapSize++] = (double)nums[i];
        totalSum += nums[i];
        heapifyUp(heapSize - 1);
    }

    double targetSum = totalSum / 2.0;
    double reducedSum = 0.0;
    int operations = 0;

    // Perform operations until the sum is reduced by at least half
    while (reducedSum < targetSum) {
        double maxElement = heap[0];
        reducedSum += maxElement / 2.0;
        heap[0] = maxElement / 2.0;
        heapifyDown(0);
        operations++;
    }

    free(heap);
    return operations;      
}
