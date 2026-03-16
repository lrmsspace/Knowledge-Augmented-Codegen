// Source: https://leetcode.com/problems/number-of-adjacent-elements-with-the-same-color/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing an array colors of length n where all elements are set to 0's meaning uncolored. You are also given a 2D integer array queries where queries[i] = [indexi, colori]. For the ith query:
//
//
// 	Set colors[indexi] to colori.
// 	Count the number of adjacent pairs in colors which have the same color (regardless of colori).
//
//
// Return an array answer of the same length as queries where answer[i] is the answer to the ith query.
//
// Example:
// Input: n = 4, queries = [[0,2],[1,2],[3,1],[1,1],[2,1]]
//
// Output: [0,1,1,0,2]
//
// Explanation:
//
//
// 	Initially array colors = [0,0,0,0], where 0 denotes uncolored elements of the array.
// 	After the 1st query colors = [2,0,0,0]. The count of adjacent pairs with the same color is 0.
// 	After the 2nd query colors = [2,2,0,0]. The count of adjacent pairs with the same color is 1.
// 	After the 3rd query colors = [2,2,0,1]. The count of adjacent pairs with the same color is 1.
// 	After the 4th query colors = [2,1,0,1]. The count of adjacent pairs with the same color is 0.
// 	After the 5th query colors = [2,1,1,1]. The count of adjacent pairs with the same color is 2.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= indexi <= n - 1
// 	1 <=  colori <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* colorTheArray(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int *colors = (int *)calloc(n, sizeof(int));
    int *result = (int *)malloc(queriesSize * sizeof(int));
    int adjacentCount = 0;

    for (int i = 0; i < queriesSize; i++) {
        int index = queries[i][0];
        int newColor = queries[i][1];
        int oldColor = colors[index];

        // Check left neighbor
        if (index > 0) {
            if (colors[index - 1] == oldColor && oldColor != 0) {
                adjacentCount--;
            }
            if (colors[index - 1] == newColor && newColor != 0) {
                adjacentCount++;
            }
        }

        // Check right neighbor
        if (index < n - 1) {
            if (colors[index + 1] == oldColor && oldColor != 0) {
                adjacentCount--;
            }
            if (colors[index + 1] == newColor && newColor != 0) {
                adjacentCount++;
            }
        }

        // Update the color
        colors[index] = newColor;

        // Store the result for this query
        result[i] = adjacentCount;
    }

    free(colors);
    *returnSize = queriesSize;
    return result;      
}
