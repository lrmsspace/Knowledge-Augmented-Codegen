// Source: https://leetcode.com/problems/k-th-nearest-obstacle-queries/   |   Difficulty: Medium
//
// Problem Description:
// There is an infinite 2D plane.
//
// You are given a positive integer k. You are also given a 2D array queries, which contains the following queries:
//
//
// 	queries[i] = [x, y]: Build an obstacle at coordinate (x, y) in the plane. It is guaranteed that there is no obstacle at this coordinate when this query is made.
//
//
// After each query, you need to find the distance of the kth nearest obstacle from the origin.
//
// Return an integer array results where results[i] denotes the kth nearest obstacle after query i, or results[i] == -1 if there are less than k obstacles.
//
// Note that initially there are no obstacles anywhere.
//
// The distance of an obstacle at coordinate (x, y) from the origin is given by |x| + |y|.
//
// Example:
// Input: queries = [[1,2],[3,4],[2,3],[-3,0]], k = 2
//
// Output: [-1,7,5,3]
//
// Explanation:
//
//
// 	Initially, there are 0 obstacles.
// 	After queries[0], there are less than 2 obstacles.
// 	After queries[1], there are obstacles at distances 3 and 7.
// 	After queries[2], there are obstacles at distances 3, 5, and 7.
// 	After queries[3], there are obstacles at distances 3, 3, 5, and 7.
//
// Constraints:
// 1 <= queries.length <= 2 * 105
// 	All queries[i] are unique.
// 	-109 <= queries[i][0], queries[i][1] <= 109
// 	1 <= k <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultsArray(int** queries, int queriesSize, int* queriesColSize, int k, int* returnSize) {
    int *res = (int *)malloc(sizeof(int) * queriesSize);
    *returnSize = queriesSize;

    // Max-heap to store the k smallest distances
    int *heap = (int *)malloc(sizeof(int) * (k + 1));
    int heapSize = 0;

    for (int i = 0; i < queriesSize; i++) {
        int dist = abs(queries[i][0]) + abs(queries[i][1]);

        // Insert distance into max-heap
        if (heapSize < k) {
            heap[++heapSize] = dist;
            // Bubble up
            for (int j = heapSize; j > 1 && heap[j] > heap[j / 2]; j /= 2) {
                int temp = heap[j];
                heap[j] = heap[j / 2];
                heap[j / 2] = temp;
            }
        } else if (dist < heap[1]) {
            heap[1] = dist;
            // Bubble down
            for (int j = 1; ; ) {
                int left = j * 2;
                int right = j * 2 + 1;
                int largest = j;

                if (left <= heapSize && heap[left] > heap[largest]) {
                    largest = left;
                }
                if (right <= heapSize && heap[right] > heap[largest]) {
                    largest = right;
                }
                if (largest == j) break;

                int temp = heap[j];
                heap[j] = heap[largest];
                heap[largest] = temp;
                j = largest;
            }
        }

        res[i] = (heapSize < k) ? -1 : heap[1];
    }

    free(heap);
    return res;     
}
