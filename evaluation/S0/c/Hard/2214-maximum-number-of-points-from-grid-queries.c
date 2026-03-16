// Source: https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid and an array queries of size k.
//
// Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:
//
//
// 	If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
// 	Otherwise, you do not get any points, and you end this process.
//
//
// After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.
//
// Return the resulting array answer.
//
// Example:
// Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
// Output: [5,8,1]
// Explanation: The diagrams above show which cells we visit to get points for each query.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	k == queries.length
// 	1 <= k <= 104
// 	1 <= grid[i][j], queries[i] <= 106
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxPoints(int** grid, int gridSize, int* gridColSize, int* queries, int queriesSize, int* returnSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int totalCells = m * n;

    // Create cells array
    typedef struct {
        int value;
        int x;
        int y;
    } Cell;

    Cell* cells = (Cell*)malloc(totalCells * sizeof(Cell));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cells[i * n + j].value = grid[i][j];
            cells[i * n + j].x = i;
            cells[i * n + j].y = j;
        }
    }

    // Sort cells by value
    int compareCells(const void* a, const void* b) {
        return ((Cell*)a)->value - ((Cell*)b)->value;
    }
    qsort(cells, totalCells, sizeof(Cell), compareCells);

    // Prepare queries with original indices
    typedef struct {
        int value;
        int index;
    } Query;

    Query* queryList = (Query*)malloc(queriesSize * sizeof(Query));
    for (int i = 0; i < queriesSize; i++) {
        queryList[i].value = queries[i];
        queryList[i].index = i;
    }

    // Sort queries by value
    int compareQueries(const void* a, const void* b) {
        return ((Query*)a)->value - ((Query*)b)->value;
    }
    qsort(queryList, queriesSize, sizeof(Query), compareQueries);

    // Result array
    int* result = (int*)malloc(queriesSize * sizeof(int));

    // Process each query
    int cellIndex = 0;
    for (int i = 0; i < queriesSize; i++) {
        int queryValue = queryList[i].value;
        int count = 0;

        while (cellIndex < totalCells && cells[cellIndex].value < queryValue) {
            count++;
            cellIndex++;
        }

        result[queryList[i].index] = count;
    }

    free(cells);
    free(queryList);

    *returnSize = queriesSize;
    return result;
}
