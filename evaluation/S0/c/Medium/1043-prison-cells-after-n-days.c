// Source: https://leetcode.com/problems/prison-cells-after-n-days/   |   Difficulty: Medium
//
// Problem Description:
// There are 8 prison cells in a row and each cell is either occupied or vacant.
//
// Each day, whether the cell is occupied or vacant changes according to the following rules:
//
//
// 	If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
// 	Otherwise, it becomes vacant.
//
//
// Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.
//
// You are given an integer array cells where cells[i] == 1 if the ith cell is occupied and cells[i] == 0 if the ith cell is vacant, and you are given an integer n.
//
// Return the state of the prison after n days (i.e., n such changes described above).
//
// Example:
// Input: cells = [0,1,0,1,1,0,0,1], n = 7
// Output: [0,0,1,1,0,0,0,0]
// Explanation: The following table summarizes the state of the prison on each day:
// Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
// Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
// Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
// Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
// Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
// Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
// Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
// Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
//
// Constraints:
// cells.length == 8
// 	cells[i] is either 0 or 1.
// 	1 <= n <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* prisonAfterNDays(int* cells, int cellsSize, int n, int* returnSize) {
    int seen[256] = {0};
    int states[256][8];
    int cycle_length = 0;
    int i, j;

    for (i = 0; i < n; i++) {
        int state = 0;
        for (j = 0; j < 8; j++) {
            state = (state << 1) | cells[j];
        }

        if (seen[state]) {
            cycle_length = i - seen[state] + 1;
            break;
        }

        seen[state] = i + 1;
        for (j = 0; j < 8; j++) {
            states[i][j] = cells[j];
        }

        int new_cells[8] = {0};
        for (j = 1; j < 7; j++) {
            new_cells[j] = (cells[j - 1] == cells[j + 1]) ? 1 : 0;
        }
        for (j = 0; j < 8; j++) {
            cells[j] = new_cells[j];
        }
    }

    if (cycle_length > 0) {
        int remaining_days = (n - i) % cycle_length;
        int target_day = seen[state] - 1 + remaining_days - 1;
        for (j = 0; j < 8; j++) {
            cells[j] = states[target_day][j];
        }
    }

    int* result = (int*)malloc(8 * sizeof(int));
    for (i = 0; i < 8; i++) {
        result[i] = cells[i];
    }
    *returnSize = 8;
    return result;      
}
