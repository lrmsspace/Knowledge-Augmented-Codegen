// Source: https://leetcode.com/problems/matrix-cells-in-distance-order/   |   Difficulty: Easy
//
// Problem Description:
// You are given four integers row, cols, rCenter, and cCenter. There is a rows x cols matrix and you are on the cell with the coordinates (rCenter, cCenter).
//
// Return the coordinates of all cells in the matrix, sorted by their distance from (rCenter, cCenter) from the smallest distance to the largest distance. You may return the answer in any order that satisfies this condition.
//
// The distance between two cells (r1, c1) and (r2, c2) is |r1 - r2| + |c1 - c2|.
//
// Example:
// Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
// Output: [[0,0],[0,1]]
// Explanation: The distances from (0, 0) to other cells are: [0,1]
//
// Constraints:
// 1 <= rows, cols <= 100
// 	0 <= rCenter < rows
// 	0 <= cCenter < cols
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** allCellsDistOrder(int rows, int cols, int rCenter, int cCenter, int* returnSize, int** returnColumnSizes) {
    int total = rows * cols;
    int** result = (int**)malloc(total * sizeof(int*));
    *returnColumnSizes = (int*)malloc(total * sizeof(int));
    *returnSize = total;

    for (int i = 0; i < total; i++) {
        result[i] = (int*)malloc(2 * sizeof(int));
        (*returnColumnSizes)[i] = 2;
    }

    int index = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            result[index][0] = r;
            result[index][1] = c;
            index++;
        }
    }

    // Comparator function for qsort
    int compare(const void* a, const void* b) {
        int* cellA = *(int**)a;
        int* cellB = *(int**)b;
        int distA = abs(cellA[0] - rCenter) + abs(cellA[1] - cCenter);
        int distB = abs(cellB[0] - rCenter) + abs(cellB[1] - cCenter);
        return distA - distB;
    }

    qsort(result, total, sizeof(int*), compare);

    return result;      
}
