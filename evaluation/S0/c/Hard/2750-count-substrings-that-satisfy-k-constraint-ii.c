// Source: https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s and an integer k.
//
// You are also given a 2D integer array queries, where queries[i] = [li, ri].
//
// A binary string satisfies the k-constraint if either of the following conditions holds:
//
//
// 	The number of 0's in the string is at most k.
// 	The number of 1's in the string is at most k.
//
//
// Return an integer array answer, where answer[i] is the number of substrings of s[li..ri] that satisfy the k-constraint.
//
// Example:
// Input: s = "0001111", k = 2, queries = [[0,6]]
//
// Output: [26]
//
// Explanation:
//
// For the query [0, 6], all substrings of s[0..6] = "0001111" satisfy the k-constraint except for the substrings s[0..5] = "000111" and s[0..6] = "0001111".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
// 	1 <= k <= s.length
// 	1 <= queries.length <= 105
// 	queries[i] == [li, ri]
// 	0 <= li <= ri < s.length
// 	All queries are distinct.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* countKConstraintSubstrings(char* s, int k, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    long long *results = (long long*)malloc(queriesSize * sizeof(long long));
    if (!results) return NULL;

    int n = strlen(s);
    int *prefix0 = (int*)malloc((n + 1) * sizeof(int));
    int *prefix1 = (int*)malloc((n + 1) * sizeof(int));
    if (!prefix0 || !prefix1) {
        free(results); free(prefix0); free(prefix1);
        return NULL;
    }

    prefix0[0] = 0; prefix1[0] = 0;
    for (int i = 0; i < n; ++i) {
        prefix0[i + 1] = prefix0[i] + (s[i] == '0' ? 1 : 0);
        prefix1[i + 1] = prefix1[i] + (s[i] == '1' ? 1 : 0);
    }

    for (int q = 0; q < queriesSize; ++q) {
        int l = queries[q][0];
        int r = queries[q][1];
        long long totalSubstrings = ((long long)(r - l + 1) * (r - l + 2)) / 2;

        long long invalidCount = 0;

        // Count invalid substrings with more than k zeros
        int left = l, right = l;
        while (left <= r) {
            while (right <= r && (prefix0[right + 1] - prefix0[left]) <= k) {
                right++;
            }
            invalidCount += (r - right + 1);
            left++;
        }

        // Count invalid substrings with more than k ones
        left = l; right = l;
        while (left <= r) {
            while (right <= r && (prefix1[right + 1] - prefix1[left]) <= k) {
                right++;
            }
            invalidCount += (r - right + 1);
            left++;
        }

        results[q] = totalSubstrings - invalidCount;
    }

    free(prefix0);
    free(prefix1);
    return results;     
}
