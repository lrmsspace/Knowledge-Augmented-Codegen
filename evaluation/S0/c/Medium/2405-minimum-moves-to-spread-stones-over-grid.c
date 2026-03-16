// Source: https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer matrix grid of size 3 * 3, representing the number of stones in each cell. The grid contains exactly 9 stones, and there can be multiple stones in a single cell.
//
// In one move, you can move a single stone from its current cell to any other cell if the two cells share a side.
//
// Return the minimum number of moves required to place one stone in each cell.
//
// Example:
// Input: grid = [[1,1,0],[1,1,1],[1,2,1]]
// Output: 3
// Explanation: One possible sequence of moves to place one stone in each cell is: 
// 1- Move one stone from cell (2,1) to cell (2,2).
// 2- Move one stone from cell (2,2) to cell (1,2).
// 3- Move one stone from cell (1,2) to cell (0,2).
// In total, it takes 3 moves to place one stone in each cell of the grid.
// It can be shown that 3 is the minimum number of moves required to place one stone in each cell.
//
// Constraints:
// grid.length == grid[i].length == 3
// 	0 <= grid[i][j] <= 9
// 	Sum of grid is equal to 9.
//

int minimumMoves(int** grid, int gridSize, int* gridColSize) {
    int stones[9];
    int index = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < grid[i][j]; k++) {
                stones[index++] = i * 3 + j;
            }
        }
    }

    int minMoves = __INT_MAX__;
    int target[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    do {
        int currentMoves = 0;
        for (int i = 0; i < 9; i++) {
            int stoneRow = stones[i] / 3;
            int stoneCol = stones[i] % 3;
            int targetRow = target[i] / 3;
            int targetCol = target[i] % 3;
            currentMoves += abs(stoneRow - targetRow) + abs(stoneCol - targetCol);
        }
        if (currentMoves < minMoves) {
            minMoves = currentMoves;
        }
    } while (__builtin_permute4f(target, target + 1, target + 2, target + 3, target + 4, target + 5, target + 6, target + 7, target + 8));

    return minMoves;        
}
