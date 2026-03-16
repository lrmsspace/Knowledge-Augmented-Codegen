// Source: https://leetcode.com/problems/palindrome-rearrangement-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s having an even length n.
//
// You are also given a 0-indexed 2D integer array, queries, where queries[i] = [ai, bi, ci, di].
//
// For each query i, you are allowed to perform the following operations:
//
//
// 	Rearrange the characters within the substring s[ai:bi], where 0 <= ai <= bi < n / 2.
// 	Rearrange the characters within the substring s[ci:di], where n / 2 <= ci <= di < n.
//
//
// For each query, your task is to determine whether it is possible to make s a palindrome by performing the operations.
//
// Each query is answered independently of the others.
//
// Return a 0-indexed array answer, where answer[i] == true if it is possible to make s a palindrome by performing operations specified by the ith query, and false otherwise.
//
//
// 	A substring is a contiguous sequence of characters within a string.
// 	s[x:y] represents the substring consisting of characters from the index x to index y in s, both inclusive.
//
// Example:
// Input: s = "abcabc", queries = [[1,1,3,5],[0,2,5,5]]
// Output: [true,true]
// Explanation: In this example, there are two queries:
// In the first query:
// - a0 = 1, b0 = 1, c0 = 3, d0 = 5.
// - So, you are allowed to rearrange s[1:1] => abcabc and s[3:5] => abcabc.
// - To make s a palindrome, s[3:5] can be rearranged to become => abccba.
// - Now, s is a palindrome. So, answer[0] = true.
// In the second query:
// - a1 = 0, b1 = 2, c1 = 5, d1 = 5.
// - So, you are allowed to rearrange s[0:2] => abcabc and s[5:5] => abcabc.
// - To make s a palindrome, s[0:2] can be rearranged to become => cbaabc.
// - Now, s is a palindrome. So, answer[1] = true.
//
// Constraints:
// 2 <= n == s.length <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 4
// 	ai == queries[i][0], bi == queries[i][1]
// 	ci == queries[i][2], di == queries[i][3]
// 	0 <= ai <= bi < n / 2
// 	n / 2 <= ci <= di < n 
// 	n is even.
// 	s consists of only lowercase English letters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* canMakePalindromeQueries(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    bool *results = (bool*)malloc(queriesSize * sizeof(bool));
    if (!results) return NULL;

    int n = strlen(s);
    int half = n / 2;

    /* prefix parity array */
    int *prefixParity = (int*)malloc((half + 1) * sizeof(int));
    if (!prefixParity) {
        free(results);
        return NULL;
    }
    prefixParity[0] = 0;
    for (int i = 0; i < half; ++i) {
        prefixParity[i + 1] = prefixParity[i] ^ (1 << (s[i] - 'a'));
    }

    for (int q = 0; q < queriesSize; ++q) {
        int a = queries[q][0];
        int b = queries[q][1];
        int c = queries[q][2];
        int d = queries[q][3];

        int leftParity = prefixParity[b + 1] ^ prefixParity[a];
        int rightParity = 0;
        for (int i = c; i <= d; ++i) {
            rightParity ^= (1 << (s[i] - 'a'));
        }

        int combinedParity = leftParity ^ rightParity;
        /* Check if at most one bit is set in combinedParity */
        results[q] = (combinedParity & (combinedParity - 1)) == 0;
    }

    free(prefixParity);
    return results;     
}
