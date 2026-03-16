// Source: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.
//
// Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].
//
// Return the maximum number of subarrays possible after removing exactly one conflicting pair.
//
// Example:
// Input: n = 4, conflictingPairs = [[2,3],[1,4]]
//
// Output: 9
//
// Explanation:
//
//
// 	Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
// 	There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
// 	The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= conflictingPairs.length <= 2 * n
// 	conflictingPairs[i].length == 2
// 	1 <= conflictingPairs[i][j] <= n
// 	conflictingPairs[i][0] != conflictingPairs[i][1]
//

long long maxSubarrays(int n, int** conflictingPairs, int conflictingPairsSize, int* conflictingPairsColSize) {
    int *left = (int*)calloc(n + 1, sizeof(int));
    int *right = (int*)calloc(n + 1, sizeof(int));
    if (!left || !right) {
        free(left); free(right);
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        left[i] = 1;
        right[i] = n;
    }
    for (int i = 0; i < conflictingPairsSize; ++i) {
        int a = conflictingPairs[i][0];
        int b = conflictingPairs[i][1];
        if (a < b) {
            if (left[b] < a + 1) left[b] = a + 1;
            if (right[a] > b - 1) right[a] = b - 1;
        } else {
            if (left[a] < b + 1) left[a] = b + 1;
            if (right[b] > a - 1) right[b] = a - 1;
        }
    }

    long long total = ((long long)n * (n + 1)) / 2;
    long long maxGain = 0;

    long long currGain = 0;
    int r = 1;
    for (int i = 1; i <= n; ++i) {
        if (r < i) r = i;
        while (r <= n && r < left[i]) {
            currGain += (n - r + 1);
            r++;
        }
        if (maxGain < currGain) maxGain = currGain;
        currGain -= (n - left[i] + 1);
    }

    free(left);
    free(right);
    return total + maxGain;     
}
