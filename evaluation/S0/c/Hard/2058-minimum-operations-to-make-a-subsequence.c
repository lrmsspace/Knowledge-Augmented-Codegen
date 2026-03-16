// Source: https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array target that consists of distinct integers and another integer array arr that can have duplicates.
//
// In one operation, you can insert any integer at any position in arr. For example, if arr = [1,4,1,2], you can add 3 in the middle and make it [1,4,3,1,2]. Note that you can insert the integer at the very beginning or end of the array.
//
// Return the minimum number of operations needed to make target a subsequence of arr.
//
// A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
//
// Example:
// Input: target = [5,1,3], arr = [9,4,2,3,4]
// Output: 2
// Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
//
// Constraints:
// 1 <= target.length, arr.length <= 105
// 	1 <= target[i], arr[i] <= 109
// 	target contains no duplicates.
//

int minOperations(int* target, int targetSize, int* arr, int arrSize) {
    int *pos = (int*)malloc((targetSize + 1) * sizeof(int));
    if (!pos) return -1; /* allocation failure */

    for (int i = 0; i < targetSize; ++i) {
        pos[target[i]] = i + 1; /* use 1-based index to distinguish from default 0 */
    }

    int *seq = (int*)malloc(arrSize * sizeof(int));
    if (!seq) { free(pos); return -1; } /* allocation failure */

    int seqLen = 0;
    for (int i = 0; i < arrSize; ++i) {
        int p = pos[arr[i]];
        if (p > 0) {
            seq[seqLen++] = p;
        }
    }

    /* find length of longest increasing subsequence in seq */
    int *lis = (int*)malloc((seqLen + 1) * sizeof(int));
    if (!lis) { free(pos); free(seq); return -1; } /* allocation failure */

    int lisLen = 0;
    for (int i = 0; i < seqLen; ++i) {
        int left = 0, right = lisLen;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (lis[mid] < seq[i]) left = mid + 1;
            else right = mid;
        }
        lis[left] = seq[i];
        if (left == lisLen) lisLen++;
    }

    free(pos);
    free(seq);
    free(lis);

    return targetSize - lisLen;     
}
