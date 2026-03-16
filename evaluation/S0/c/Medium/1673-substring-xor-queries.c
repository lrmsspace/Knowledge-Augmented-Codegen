// Source: https://leetcode.com/problems/substring-xor-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s, and a 2D integer array queries where queries[i] = [firsti, secondi].
//
// For the ith query, find the shortest substring of s whose decimal value, val, yields secondi when bitwise XORed with firsti. In other words, val ^ firsti == secondi.
//
// The answer to the ith query is the endpoints (0-indexed) of the substring [lefti, righti] or [-1, -1] if no such substring exists. If there are multiple answers, choose the one with the minimum lefti.
//
// Return an array ans where ans[i] = [lefti, righti] is the answer to the ith query.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "101101", queries = [[0,5],[1,2]]
// Output: [[0,2],[2,3]]
// Explanation: For the first query the substring in range [0,2] is "101" which has a decimal value of 5, and 5 ^ 0 = 5, hence the answer to the first query is [0,2]. In the second query, the substring in range [2,3] is "11", and has a decimal value of 3, and 3 ^ 1 = 2. So, [2,3] is returned for the second query.
//
// Constraints:
// 1 <= s.length <= 104
// 	s[i] is either '0' or '1'.
// 	1 <= queries.length <= 105
// 	0 <= firsti, secondi <= 109
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** substringXorQueries(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize, int** returnColumnSizes) {
    int maxLen = 32; // Since 2^30 > 10^9, we only need to consider substrings of length up to 30
    int n = strlen(s);
    int totalSubstrings = 0;

    // Calculate the total number of substrings to allocate memory
    for (int len = 1; len <= maxLen && len <= n; len++) {
        totalSubstrings += (n - len + 1);
    }

    // Allocate memory for storing substring values and their indices
    int (*substrings)[3] = malloc(totalSubstrings * sizeof(*substrings));
    int idx = 0;

    // Generate all possible substrings and store their values and indices
    for (int len = 1; len <= maxLen && len <= n; len++) {
        for (int start = 0; start <= n - len; start++) {
            int value = 0;
            for (int k = 0; k < len; k++) {
                value = (value << 1) | (s[start + k] - '0');
            }
            substrings[idx][0] = value;
            substrings[idx][1] = start;
            substrings[idx][2] = start + len - 1;
            idx++;
        }
    }

    // Sort the substrings based on their values
    qsort(substrings, totalSubstrings, sizeof(*substrings), [](const void* a, const void* b) {
        return (*(int (*)[3])a)[0] - (*(int (*)[3])b)[0];
    });

    // Prepare the result array
    int** result = malloc(queriesSize * sizeof(int*));
    *returnColumnSizes = malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    // Process each query
    for (int i = 0; i < queriesSize; i++) {
        int first = queries[i][0];
        int second = queries[i][1];
        int target = first ^ second;

        // Binary search for the target value in substrings
        int left = 0, right = totalSubstrings - 1;
        int found = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (substrings[mid][0] == target) {
                found = mid;
                right = mid - 1; // Look for the first occurrence
            } else if (substrings[mid][0] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        result[i] = malloc(2 * sizeof(int));
        (*returnColumnSizes)[i] = 2;

        if (found != -1) {
            result[i][0] = substrings[found][1];
            result[i][1] = substrings[found][2];
        } else {
            result[i][0] = -1;
            result[i][1] = -1;
        }
    }
    free(substrings);
    return result;
}
