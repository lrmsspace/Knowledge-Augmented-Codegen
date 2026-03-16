// Source: https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array heights of positive integers, where heights[i] represents the height of the ith building.
//
// If a person is in building i, they can move to any other building j if and only if i < j and heights[i] < heights[j].
//
// You are also given another array queries where queries[i] = [ai, bi]. On the ith query, Alice is in building ai while Bob is in building bi.
//
// Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can meet on the ith query. If Alice and Bob cannot move to a common building on query i, set ans[i] to -1.
//
// Example:
// Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
// Output: [2,5,-1,5,2]
// Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2]. 
// In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5]. 
// In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
// In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
// In the fifth query, Alice and Bob are already in the same building.  
// For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
// For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.
//
// Constraints:
// 1 <= heights.length <= 5 * 104
// 	1 <= heights[i] <= 109
// 	1 <= queries.length <= 5 * 104
// 	queries[i] = [ai, bi]
// 	0 <= ai, bi <= heights.length - 1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* leftmostBuildingQueries(int* heights, int heightsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;

    /* Preprocess next greater element to the right using a stack */
    int *nextGreater = (int*)malloc(heightsSize * sizeof(int));
    if (!nextGreater) {
        free(results);
        return NULL;
    }
    for (int i = 0; i < heightsSize; ++i) nextGreater[i] = -1;

    int *stack = (int*)malloc(heightsSize * sizeof(int));
    if (!stack) {
        free(results);
        free(nextGreater);
        return NULL;
    }
    int top = -1;

    for (int i = 0; i < heightsSize; ++i) {
        while (top >= 0 && heights[stack[top]] < heights[i]) {
            nextGreater[stack[top--]] = i;
        }
        stack[++top] = i;
    }
    free(stack);

    /* Process each query */
    for (int q = 0; q < queriesSize; ++q) {
        int a = queries[q][0];
        int b = queries[q][1];
        if (a == b) {
            results[q] = a;
            continue;
        }
        int start = a < b ? a : b;
        int end = a > b ? a : b;

        int pos = start;
        while (pos != -1 && pos < end) {
            pos = nextGreater[pos];
        }
        results[q] = (pos != -1) ? pos : -1;
    }

    free(nextGreater);
    return results;     
}
