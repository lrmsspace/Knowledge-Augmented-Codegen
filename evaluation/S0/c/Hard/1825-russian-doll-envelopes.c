// Source: https://leetcode.com/problems/russian-doll-envelopes/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
//
// One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
//
// Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
//
// Note: You cannot rotate an envelope.
//
// Example:
// Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
// Output: 3
// Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
//
// Constraints:
// 1 <= envelopes.length <= 105
// 	envelopes[i].length == 2
// 	1 <= wi, hi <= 105
//

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {
    if (envelopesSize == 0 || !envelopesColSize) return 0;

    // Sort envelopes: first by width ascending, then by height descending
    int cmp(const void *a, const void *b) {
        int wa = (*(int**)a)[0], ha = (*(int**)a)[1];
        int wb = (*(int**)b)[0], hb = (*(int**)b)[1];
        if (wa != wb) return wa - wb;
        return hb - ha;
    }
    qsort(envelopes, envelopesSize, sizeof(int*), cmp);

    // Extract heights and find LIS
    int *heights = (int*)malloc(envelopesSize * sizeof(int));
    for (int i = 0; i < envelopesSize; ++i) {
        heights[i] = envelopes[i][1];
    }

    int *dp = (int*)malloc((envelopesSize + 1) * sizeof(int));
    int length = 0;
    for (int i = 0; i < envelopesSize; ++i) {
        int h = heights[i];
        int left = 1, right = length;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (dp[mid] < h) left = mid + 1;
            else right = mid - 1;
        }
        dp[left] = h;
        if (left > length) length = left;
    }

    free(heights);
    free(dp);
    return length;      
}
