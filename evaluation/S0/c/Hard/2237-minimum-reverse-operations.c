// Source: https://leetcode.com/problems/minimum-reverse-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an integer p representing an array arr of length n where all elements are set to 0's, except position p which is set to 1. You are also given an integer array banned containing restricted positions. Perform the following operation on arr:
//
//
// 	Reverse a subarray with size k if the single 1 is not set to a position in banned.
//
//
// Return an integer array answer with n results where the ith result is the minimum number of operations needed to bring the single 1 to position i in arr, or -1 if it is impossible.
//
// Example:
// Input: n = 4, p = 0, banned = [1,2], k = 4
//
// Output: [0,-1,-1,1]
//
// Explanation:
//
//
// 	Initially 1 is placed at position 0 so the number of operations we need for position 0 is 0.
// 	We can never place 1 on the banned positions, so the answer for positions 1 and 2 is -1.
// 	Perform the operation of size 4 to reverse the whole array.
// 	After a single operation 1 is at position 3 so the answer for position 3 is 1.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= p <= n - 1
// 	0 <= banned.length <= n - 1
// 	0 <= banned[i] <= n - 1
// 	1 <= k <= n 
// 	banned[i] != p
// 	all values in banned are unique
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minReverseOperations(int n, int p, int* banned, int bannedSize, int k, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = n;
    int *res = (int*)malloc(n * sizeof(int));
    if (!res) return NULL;
    for (int i = 0; i < n; ++i) res[i] = -1;
    int *isBanned = (int*)calloc(n, sizeof(int));
    if (!isBanned) { free(res); return NULL; }
    for (int i = 0; i < bannedSize; ++i) isBanned[banned[i]] = 1;

    int half = k / 2;
    int sizeEven = (n + 1) / 2;
    int sizeOdd = n / 2;
    int *nextEven = (int*)malloc(sizeEven * sizeof(int));
    int *nextOdd = (int*)malloc(sizeOdd * sizeof(int));
    if (!nextEven || !nextOdd) {
        free(res); free(isBanned); free(nextEven); free(nextOdd);
        return NULL;
    }
    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < n; ++i) {
        if (isBanned[i] || i == p) continue;
        if (i % 2 == 0) nextEven[evenCount++] = i;
        else nextOdd[oddCount++] = i;
    }

    int *queue = (int*)malloc(n * sizeof(int));
    if (!queue) {
        free(res); free(isBanned); free(nextEven); free(nextOdd);
        return NULL;
    }
    int front = 0, back = 0;
    queue[back++] = p;
    res[p] = 0;

    while (front < back) {
        int curr = queue[front++];
        int currDist = res[curr];
        int left = curr - (k - 1);
        if (left < 0) left = 0;
        int right = curr + (k - 1);
        if (right >= n) right = n - 1;
        int start = left + (k - 1) - (curr - left);
        if (start < left) start += 2;
        int *nextArray = (start % 2 == 0) ? nextEven : nextOdd;
        int nextSize = (start % 2 == 0) ? evenCount : oddCount;
        for (int i = 0; i < nextSize; ) {
            int pos = nextArray[i];
            if (pos < start) {
                ++i;
                continue;
            }
            if (pos > right) break;
            res[pos] = currDist + 1;
            queue[back++] = pos;
            /* remove pos from nextArray */
            nextArray[i] = nextArray[--nextSize];
        }
        if (start % 2 == 0) evenCount = nextSize;
        else oddCount = nextSize;
    }   
    free(isBanned);
    free(nextEven);
    free(nextOdd);
    free(queue);
    return res;
}
