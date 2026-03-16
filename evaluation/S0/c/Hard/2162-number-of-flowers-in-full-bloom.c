// Source: https://leetcode.com/problems/number-of-flowers-in-full-bloom/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array flowers, where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive). You are also given a 0-indexed integer array people of size n, where people[i] is the time that the ith person will arrive to see the flowers.
//
// Return an integer array answer of size n, where answer[i] is the number of flowers that are in full bloom when the ith person arrives.
//
// Example:
// Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
// Output: [1,2,2,2]
// Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
// For each person, we return the number of flowers in full bloom during their arrival.
//
// Constraints:
// 1 <= flowers.length <= 5 * 104
// 	flowers[i].length == 2
// 	1 <= starti <= endi <= 109
// 	1 <= people.length <= 5 * 104
// 	1 <= people[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* fullBloomFlowers(int** flowers, int flowersSize, int* flowersColSize, int* people, int peopleSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = peopleSize;
    if (flowersSize <= 0 || peopleSize <= 0) return NULL;

    int n = flowersSize;
    int *starts = (int*)malloc(n * sizeof(int));
    int *ends = (int*)malloc(n * sizeof(int));
    if (!starts || !ends) {
        free(starts); free(ends);
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        starts[i] = flowers[i][0];
        ends[i] = flowers[i][1];
    }

    // Comparison function for qsort
    int cmpInt(const void *a, const void *b) {
        return (*(int*)a) - (*(int*)b);
    }

    qsort(starts, n, sizeof(int), cmpInt);
    qsort(ends, n, sizeof(int), cmpInt);

    int* result = (int*)malloc(peopleSize * sizeof(int));
    if (!result) {
        free(starts); free(ends);
        return NULL;
    }

    for (int i = 0; i < peopleSize; ++i) {
        int p = people[i];
        // Count of flowers that have started blooming
        int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (starts[mid] <= p) left = mid + 1;
            else right = mid;
        }
        int started = left;

        // Count of flowers that have ended blooming
        left = 0; right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (ends[mid] < p) left = mid + 1;
            else right = mid;
        }
        int ended = left;

        result[i] = started - ended;
    }

    free(starts);
    free(ends);
    return result;      
}
