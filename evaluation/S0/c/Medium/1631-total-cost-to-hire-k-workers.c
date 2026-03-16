// Source: https://leetcode.com/problems/total-cost-to-hire-k-workers/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.
//
// You are also given two integers k and candidates. We want to hire exactly k workers according to the following rules:
//
//
// 	You will run k sessions and hire exactly one worker in each session.
// 	In each hiring session, choose the worker with the lowest cost from either the first candidates workers or the last candidates workers. Break the tie by the smallest index.
// 	
// 		For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session, we will choose the 4th worker because they have the lowest cost [3,2,7,7,1,2].
// 		In the second hiring session, we will choose 1st worker because they have the same lowest cost as 4th worker but they have the smallest index [3,2,7,7,2]. Please note that the indexing may be changed in the process.
// 	
// 	
// 	If there are fewer than candidates workers remaining, choose the worker with the lowest cost among them. Break the tie by the smallest index.
// 	A worker can only be chosen once.
//
//
// Return the total cost to hire exactly k workers.
//
// Example:
// Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
// Output: 11
// Explanation: We hire 3 workers in total. The total cost is initially 0.
// - In the first hiring round we choose the worker from [17,12,10,2,7,2,11,20,8]. The lowest cost is 2, and we break the tie by the smallest index, which is 3. The total cost = 0 + 2 = 2.
// - In the second hiring round we choose the worker from [17,12,10,7,2,11,20,8]. The lowest cost is 2 (index 4). The total cost = 2 + 2 = 4.
// - In the third hiring round we choose the worker from [17,12,10,7,11,20,8]. The lowest cost is 7 (index 3). The total cost = 4 + 7 = 11. Notice that the worker with index 3 was common in the first and last four workers.
// The total hiring cost is 11.
//
// Constraints:
// 1 <= costs.length <= 105 
// 	1 <= costs[i] <= 105
// 	1 <= k, candidates <= costs.length
//

long long totalCost(int* costs, int costsSize, int k, int candidates) {
    long long total = 0;
    int left = 0, right = costsSize - 1;
    int hired = 0;

    // Min-heaps for the left and right candidates
    int leftHeap[candidates];
    int rightHeap[candidates];
    int leftSize = 0, rightSize = 0;

    // Function to insert into min-heap
    void insertHeap(int* heap, int* size, int val) {
        heap[(*size)++] = val;
        for (int i = (*size) - 1; i > 0; ) {
            int parent = (i - 1) / 2;
            if (heap[parent] <= heap[i]) break;
            int temp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = temp;
            i = parent;
        }
    }

    // Function to extract min from min-heap
    int extractMin(int* heap, int* size) {
        int minVal = heap[0];
        heap[0] = heap[--(*size)];
        for (int i = 0; ; ) {
            int leftChild = 2 * i + 1;
            int rightChild = 2 * i + 2;
            int smallest = i;

            if (leftChild < *size && heap[leftChild] < heap[smallest]) smallest = leftChild;
            if (rightChild < *size && heap[rightChild] < heap[smallest]) smallest = rightChild;

            if (smallest == i) break;

            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        }
        return minVal;
    }

    // Initialize heaps with candidates
    while (left < candidates && left <= right) {
        insertHeap(leftHeap, &leftSize, costs[left++]);
    }
    while (right >= costsSize - candidates && right >= left) {
        insertHeap(rightHeap, &rightSize, costs[right--]);
    }

    // Hire k workers
    while (hired < k) {
        if (leftSize == 0) {
            total += extractMin(rightHeap, &rightSize);
            if (right >= left) {
                insertHeap(rightHeap, &rightSize, costs[right--]);
            }
        } else if (rightSize == 0) {
            total += extractMin(leftHeap, &leftSize);
            if (left <= right) {
                insertHeap(leftHeap, &leftSize, costs[left++]);
            }
        } else {
            if (leftHeap[0] <= rightHeap[0]) {
                total += extractMin(leftHeap, &leftSize);
                if (left <= right) {
                    insertHeap(leftHeap, &leftSize, costs[left++]);
                }
            } else {
                total += extractMin(rightHeap, &rightSize);
                if (right >= left) {
                    insertHeap(rightHeap, &rightSize, costs[right--]);
                }
            }
        }
        hired++;
    }
    return total;       
}
