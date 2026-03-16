// Source: https://leetcode.com/problems/maximum-subsequence-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of equal length n and a positive integer k. You must choose a subsequence of indices from nums1 of length k.
//
// For chosen indices i0, i1, ..., ik - 1, your score is defined as:
//
//
// 	The sum of the selected elements from nums1 multiplied with the minimum of the selected elements from nums2.
// 	It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).
//
//
// Return the maximum possible score.
//
// A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1} by deleting some or no elements.
//
// Example:
// Input: nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
// Output: 12
// Explanation: 
// The four possible subsequence scores are:
// - We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3) = 7.
// - We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4) = 6. 
// - We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4) = 12. 
// - We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4) = 8.
// Therefore, we return the max score, which is 12.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	0 <= nums1[i], nums2[j] <= 105
// 	1 <= k <= n
//

long long maxScore(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    typedef struct {
        int val1;
        int val2;
    } Pair;

    int compare(const void* a, const void* b) {
        Pair* p1 = (Pair*)a;
        Pair* p2 = (Pair*)b;
        return p2->val2 - p1->val2; // Sort in descending order based on val2
    }

    Pair* pairs = (Pair*)malloc(nums1Size * sizeof(Pair));
    for (int i = 0; i < nums1Size; i++) {
        pairs[i].val1 = nums1[i];
        pairs[i].val2 = nums2[i];
    }

    qsort(pairs, nums1Size, sizeof(Pair), compare);

    long long max_score = 0;
    long long current_sum = 0;
    int* min_heap = (int*)malloc(k * sizeof(int));
    int heap_size = 0;

    for (int i = 0; i < nums1Size; i++) {
        if (heap_size < k) {
            min_heap[heap_size++] = pairs[i].val1;
            current_sum += pairs[i].val1;
            if (heap_size == k) {
                long long score = current_sum * pairs[i].val2;
                if (score > max_score) {
                    max_score = score;
                }
            }
        } else if (pairs[i].val1 > min_heap[0]) {
            current_sum -= min_heap[0];
            current_sum += pairs[i].val1;
            min_heap[0] = pairs[i].val1;

            // Re-heapify the min-heap
            for (int j = 0; j < k / 2; j++) {
                int smallest = j;
                int left = 2 * j + 1;
                int right = 2 * j + 2;

                if (left < k && min_heap[left] < min_heap[smallest]) {
                    smallest = left;
                }
                if (right < k && min_heap[right] < min_heap[smallest]) {
                    smallest = right;
                }
                if (smallest != j) {
                    int temp = min_heap[j];
                    min_heap[j] = min_heap[smallest];
                    min_heap[smallest] = temp;
                } else {
                    break;
                }
            }      
            long long score = current_sum * pairs[i].val2;
            if (score > max_score) {
                max_score = score;
            }
        }
    }
    free(pairs);
    free(min_heap);
    return max_score; 
}
