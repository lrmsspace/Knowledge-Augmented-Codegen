// Source: https://leetcode.com/problems/make-array-strictly-increasing/   |   Difficulty: Hard
//
// Problem Description:
// Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
//
// In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
//
// If there is no way to make arr1 strictly increasing, return -1.
//
// Example:
// Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
// Output: 1
// Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 2000
// 	0 <= arr1[i], arr2[i] <= 10^9
//

int makeArrayIncreasing(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    int *dp = (int*)malloc((arr1Size + 1) * sizeof(int));
    if (!dp) return -1;
    for (int i = 0; i <= arr1Size; ++i) dp[i] = 0x7FFFFFFF;
    dp[0] = -1;

    /* sort and unique arr2 */
    qsort(arr2, arr2Size, sizeof(int), cmpInt);
    int uniqueSize = 0;
    for (int i = 0; i < arr2Size; ++i) {
        if (i == 0 || arr2[i] != arr2[i - 1]) {
            arr2[uniqueSize++] = arr2[i];
        }
    }

    for (int i = 0; i < arr1Size; ++i) {
        int *newDp = (int*)malloc((arr1Size + 1) * sizeof(int));
        if (!newDp) { free(dp); return -1; }
        for (int j = 0; j <= arr1Size; ++j) newDp[j] = 0x7FFFFFFF;

        for (int j = 0; j <= arr1Size; ++j) {
            if (dp[j] < arr1[i]) {
                if (arr1[i] < newDp[j]) {
                    newDp[j] = arr1[i];
                }
            }
            if (j < arr1Size) {
                /* binary search in arr2 */
                int left = 0, right = uniqueSize - 1, pos = -1;
                while (left <= right) {
                    int mid = left + (right - left) / 2;
                    if (arr2[mid] > dp[j]) {
                        pos = mid;
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
                if (pos != -1 && arr2[pos] < newDp[j + 1]) {
                    newDp[j + 1] = arr2[pos];
                }
            }
        }
        free(dp);
        dp = newDp;
    }

    int result = -1;
    for (int i = 0; i <= arr1Size; ++i) {
        if (dp[i] != 0x7FFFFFFF) {
            result = i;
            break;
        }
    }
    free(dp);
    return result;
}
