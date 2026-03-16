// Source: https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer limit and a 2D array queries of size n x 2.
//
// There are limit + 1 balls with distinct labels in the range [0, limit]. Initially, all balls are uncolored. For every query in queries that is of the form [x, y], you mark ball x with the color y. After each query, you need to find the number of colors among the balls.
//
// Return an array result of length n, where result[i] denotes the number of colors after ith query.
//
// Note that when answering a query, lack of a color will not be considered as a color.
//
// Example:
// Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
//
// Output: [1,2,2,3]
//
// Explanation:
//
//
//
//
// 	After query 0, ball 1 has color 4.
// 	After query 1, ball 1 has color 4, and ball 2 has color 5.
// 	After query 2, ball 1 has color 3, and ball 2 has color 5.
// 	After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has color 4.
//
// Constraints:
// 1 <= limit <= 109
// 	1 <= n == queries.length <= 105
// 	queries[i].length == 2
// 	0 <= queries[i][0] <= limit
// 	1 <= queries[i][1] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* queryResults(int limit, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int* result = (int*)malloc(queriesSize * sizeof(int));
    int* ballColors = (int*)calloc(limit + 1, sizeof(int));
    int distinctColorCount = 0;

    for (int i = 0; i < queriesSize; i++) {
        int ball = queries[i][0];
        int color = queries[i][1];

        if (ballColors[ball] == 0) {
            distinctColorCount++;
        }
        ballColors[ball] = color;
        result[i] = distinctColorCount;
    }

    free(ballColors);
    *returnSize = queriesSize;
    return result;      
}
