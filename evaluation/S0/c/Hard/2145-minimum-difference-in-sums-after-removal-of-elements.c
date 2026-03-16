// Source: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums consisting of 3 * n elements.
//
// You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:
//
//
// 	The first n elements belonging to the first part and their sum is sumfirst.
// 	The next n elements belonging to the second part and their sum is sumsecond.
//
//
// The difference in sums of the two parts is denoted as sumfirst - sumsecond.
//
//
// 	For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
// 	Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
//
//
// Return the minimum difference possible between the sums of the two parts after the removal of n elements.
//
// Example:
// Input: nums = [3,1,2]
// Output: -1
// Explanation: Here, nums has 3 elements, so n = 1. 
// Thus we have to remove 1 element from nums and divide the array into two equal parts.
// - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
// - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
// - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
// The minimum difference between sums of the two parts is min(-1,1,2) = -1.
//
// Constraints:
// nums.length == 3 * n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 105
//

long long minimumDifference(int* nums, int numsSize) {
    int n = numsSize / 3;
    long long totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    // Min-heap for the first part
    long long firstPartSum = 0;
    int* minHeap = (int*)malloc((n + 1) * sizeof(int));
    int minHeapSize = 0;

    for (int i = 0; i < n; i++) {
        firstPartSum += nums[i];
        minHeap[minHeapSize++] = nums[i];
    }
    // Build min-heap
    for (int i = (minHeapSize - 2) / 2; i >= 0; i--) {
        int parent = i;
        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int smallest = parent;
            if (left < minHeapSize && minHeap[left] < minHeap[smallest]) {
                smallest = left;
            }
            if (right < minHeapSize && minHeap[right] < minHeap[smallest]) {
                smallest = right;
            }
            if (smallest == parent) break;
            int temp = minHeap[parent];
            minHeap[parent] = minHeap[smallest];
            minHeap[smallest] = temp;
            parent = smallest;
        }
    }

    long long* firstPartSums = (long long*)malloc((n + 1) * sizeof(long long));
    firstPartSums[0] = firstPartSum;

    for (int i = n; i < 2 * n; i++) {
        if (nums[i] > minHeap[0]) {
            firstPartSum += nums[i] - minHeap[0];
            firstPartSums[i - n + 1] = firstPartSum;

            // Replace root of min-heap
            minHeap[0] = nums[i];
            // Heapify down
            int parent = 0;
            while (1) {
                int left = 2 * parent + 1;
                int right = 2 * parent + 2;
                int smallest = parent;
                if (left < minHeapSize && minHeap[left] < minHeap[smallest]) {
                    smallest = left;
                }
                if (right < minHeapSize && minHeap[right] < minHeap[smallest]) {
                    smallest = right;
                }
                if (smallest == parent) break;
                int temp = minHeap[parent];
                minHeap[parent] = minHeap[smallest];
                minHeap[smallest] = temp;
                parent = smallest;
            }
        } else {
            firstPartSums[i - n + 1] = firstPartSum;
        }
    }
    free(minHeap);
    // Max-heap for the second part
    long long secondPartSum = 0;
    int* maxHeap = (int*)malloc((n + 1) * sizeof(int));
    int maxHeapSize = 0;
    for (int i = numsSize - 1; i >= 2 * n; i--) {
        secondPartSum += nums[i];
        maxHeap[maxHeapSize++] = nums[i];
    }
    // Build max-heap
    for (int i = (maxHeapSize - 2) / 2; i >= 0; i--) {
        int parent = i;
        while (1) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int largest = parent;
            if (left < maxHeapSize && maxHeap[left] > maxHeap[largest]) {
                largest = left;
            }
            if (right < maxHeapSize && maxHeap[right] > maxHeap[largest]) {
                largest = right;
            }
            if (largest == parent) break;
            int temp = maxHeap[parent];
            maxHeap[parent] = maxHeap[largest];
            maxHeap[largest] = temp;
            parent = largest;
        }
    }
    long long* secondPartSums = (long long*)malloc((n + 1) * sizeof(long long));
    secondPartSums[n] = secondPartSum;
    for (int i = 2 * n - 1; i >= n; i--) {
        if (nums[i] < maxHeap[0]) {
            secondPartSum += nums[i] - maxHeap[0];
            secondPartSums[i - n] = secondPartSum;

            // Replace root of max-heap
            maxHeap[0] = nums[i];
            // Heapify down
            int parent = 0;
            while (1) {
                int left = 2 * parent + 1;
                int right = 2 * parent + 2;
                int largest = parent;
                if (left < maxHeapSize && maxHeap[left] > maxHeap[largest]) {
                    largest = left;
                }
                if (right < maxHeapSize && maxHeap[right] > maxHeap[largest]) {
                    largest = right;
                }
                if (largest == parent) break;
                int temp = maxHeap[parent];
                maxHeap[parent] = maxHeap[largest];
                maxHeap[largest] = temp;
                parent = largest;
            }
        } else {
            secondPartSums[i - n] = secondPartSum;
        }
    }
    free(maxHeap);
    // Find minimum difference
    long long minDiff = LLONG_MAX;
    for (int i = 0; i <= n; i++) {
        long long diff = firstPartSums[i] - (totalSum - firstPartSums[i] - secondPartSums[i]);
        if (diff < minDiff) {
            minDiff = diff;
        }
    }
    free(firstPartSums);
    free(secondPartSums);
    return minDiff;
}
