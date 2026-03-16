// Source: https://leetcode.com/problems/build-a-matrix-with-conditions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer k. You are also given:
//
//
// 	a 2D integer array rowConditions of size n where rowConditions[i] = [abovei, belowi], and
// 	a 2D integer array colConditions of size m where colConditions[i] = [lefti, righti].
//
//
// The two arrays contain integers from 1 to k.
//
// You have to build a k x k matrix that contains each of the numbers from 1 to k exactly once. The remaining cells should have the value 0.
//
// The matrix should also satisfy the following conditions:
//
//
// 	The number abovei should appear in a row that is strictly above the row at which the number belowi appears for all i from 0 to n - 1.
// 	The number lefti should appear in a column that is strictly left of the column at which the number righti appears for all i from 0 to m - 1.
//
//
// Return any matrix that satisfies the conditions. If no answer exists, return an empty matrix.
//
// Example:
// Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
// Output: [[3,0,0],[0,0,1],[0,2,0]]
// Explanation: The diagram above shows a valid example of a matrix that satisfies all the conditions.
// The row conditions are the following:
// - Number 1 is in row 1, and number 2 is in row 2, so 1 is above 2 in the matrix.
// - Number 3 is in row 0, and number 2 is in row 2, so 3 is above 2 in the matrix.
// The column conditions are the following:
// - Number 2 is in column 1, and number 1 is in column 2, so 2 is left of 1 in the matrix.
// - Number 3 is in column 0, and number 2 is in column 1, so 3 is left of 2 in the matrix.
// Note that there may be multiple correct answers.
//
// Constraints:
// 2 <= k <= 400
// 	1 <= rowConditions.length, colConditions.length <= 104
// 	rowConditions[i].length == colConditions[i].length == 2
// 	1 <= abovei, belowi, lefti, righti <= k
// 	abovei != belowi
// 	lefti != righti
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** buildMatrix(int k, int** rowConditions, int rowConditionsSize, int* rowConditionsColSize, int** colConditions, int colConditionsSize, int* colConditionsColSize, int* returnSize, int** returnColumnSizes) {
    // Topological sort helper function
    int* topoSort(int k, int** conditions, int conditionsSize) {
        int* inDegree = (int*)calloc(k + 1, sizeof(int));
        int** graph = (int**)malloc((k + 1) * sizeof(int*));
        for (int i = 0; i <= k; i++) {
            graph[i] = (int*)malloc((k + 1) * sizeof(int));
            memset(graph[i], 0, (k + 1) * sizeof(int));
        }
        for (int i = 0; i < conditionsSize; i++) {
            int u = conditions[i][0];
            int v = conditions[i][1];
            if (graph[u][v] == 0) {
                graph[u][v] = 1;
                inDegree[v]++;
            }
        }
        int* queue = (int*)malloc((k + 1) * sizeof(int));
        int front = 0, rear = 0;
        for (int i = 1; i <= k; i++) {
            if (inDegree[i] == 0) {
                queue[rear++] = i;
            }
        }
        int* order = (int*)malloc((k + 1) * sizeof(int));
        int index = 0;
        while (front < rear) {
            int u = queue[front++];
            order[index++] = u;
            for (int v = 1; v <= k; v++) {
                if (graph[u][v]) {
                    inDegree[v]--;
                    if (inDegree[v] == 0) {
                        queue[rear++] = v;
                    }
                }
            }
        }
        free(inDegree);
        for (int i = 0; i <= k; i++) {
            free(graph[i]);
        }
        free(graph);
        free(queue);
        if (index != k) {
            free(order);
            return NULL;
        }
        return order;
    }

    int* rowOrder = topoSort(k, rowConditions, rowConditionsSize);
    int* colOrder = topoSort(k, colConditions, colConditionsSize);
    if (!rowOrder || !colOrder) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int** matrix = (int**)malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        matrix[i] = (int*)calloc(k, sizeof(int));
    }
    int* rowPos = (int*)malloc((k + 1) * sizeof(int));
    int* colPos = (int*)malloc((k + 1) * sizeof(int));
    for (int i = 0; i < k; i++) {
        rowPos[rowOrder[i]] = i;
        colPos[colOrder[i]] = i;
    }
    for (int i = 1; i <= k; i++) {
        matrix[rowPos[i]][colPos[i]] = i;
    }
    free(rowOrder);
    free(colOrder);
    free(rowPos);
    free(colPos);
    *returnSize = k;
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        (*returnColumnSizes)[i] = k;
    }
    return matrix;
}
