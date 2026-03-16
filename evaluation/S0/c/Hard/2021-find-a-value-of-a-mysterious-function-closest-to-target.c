// Source: https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/   |   Difficulty: Hard
//
// Problem Description:
// Winston was given the above mysterious function func. He has an integer array arr and an integer target and he wants to find the values l and r that make the value |func(arr, l, r) - target| minimum possible.
//
// Return the minimum possible value of |func(arr, l, r) - target|.
//
// Notice that func should be called with the values l and r where 0 <= l, r < arr.length.
//
// Example:
// Input: arr = [9,12,3,7,15], target = 5
// Output: 2
// Explanation: Calling func with all the pairs of [l,r] = [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]], Winston got the following results [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0]. The value closest to 5 is 7 and 3, thus the minimum difference is 2.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 106
// 	0 <= target <= 107
//

int closestToTarget(int* arr, int arrSize, int target) {
    int res = 10000000;
    int n = 0; /* number of unique ANDs ending at current position */
    int *ands = (int*)malloc(arrSize * sizeof(int));
    if (!ands) return -1; /* allocation failure */

    for (int i = 0; i < arrSize; ++i) {
        int curr = arr[i];
        ands[n++] = curr;
        for (int j = n - 2; j >= 0; --j) {
            int next = ands[j] & curr;
            if (next == ands[j]) break; /* no change, stop early */
            ands[j] = next;
        }
        for (int j = 0; j < n; ++j) {
            if (abs(ands[j] - target) < res) {
                res = abs(ands[j] - target);
                if (res == 0) { free(ands); return 0; } /* can't do better than 0 */
            }
        }
        /* remove duplicates */
        int m = 1;
        for (int j = 1; j < n; ++j) {
            if (ands[j] != ands[j-1]) {
                ands[m++] = ands[j];
            }
        }
        n = m;
    }

    free(ands);
    return res;     
}
