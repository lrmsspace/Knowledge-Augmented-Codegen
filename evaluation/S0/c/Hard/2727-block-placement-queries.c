// Source: https://leetcode.com/problems/block-placement-queries/   |   Difficulty: Hard
//
// Problem Description:
// There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.
//
// You are given a 2D array queries, which contains two types of queries:
//
//
// 	For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
// 	For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
//
//
// Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.
//
// Example:
// Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
//
// Output: [false,true,true]
//
// Explanation:
//
//
//
// For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.
//
// Constraints:
// 1 <= queries.length <= 15 * 104
// 	2 <= queries[i].length <= 3
// 	1 <= queries[i][0] <= 2
// 	1 <= x, sz <= min(5 * 104, 3 * queries.length)
// 	The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
// 	The input is generated such that there is at least one query of type 2.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* getResults(int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;

    /* Using a simple boolean array to track obstacles */
    enum { MAX_POS = 50000 + 1 };
    bool *obstacles = (bool*)calloc(MAX_POS, sizeof(bool));
    if (!obstacles) return NULL;

    bool *results = (bool*)malloc(queriesSize * sizeof(bool));
    if (!results) {
        free(obstacles);
        return NULL;
    }
    int resIdx = 0;

    for (int i = 0; i < queriesSize; ++i) {
        int qType = queries[i][0];
        if (qType == 1) {
            int x = queries[i][1];
            if (x >= 0 && x < MAX_POS) {
                obstacles[x] = true;
            }
        } else if (qType == 2) {
            int x = queries[i][1];
            int sz = queries[i][2];
            bool canPlace = true;
            for (int pos = x - sz + 1; pos <= x; ++pos) {
                if (pos >= 0 && pos < MAX_POS && obstacles[pos]) {
                    canPlace = false;
                    break;
                }
            }
            results[resIdx++] = canPlace;
        }
    }

    free(obstacles);
    *returnSize = resIdx;
    return results;     
}
