// Source: https://leetcode.com/problems/count-fertile-pyramids-in-a-land/   |   Difficulty: Hard
//
// Problem Description:
// A farmer has a rectangular grid of land with m rows and n columns that can be divided into unit cells. Each cell is either fertile (represented by a 1) or barren (represented by a 0). All cells outside the grid are considered barren.
//
// A pyramidal plot of land can be defined as a set of cells with the following criteria:
//
//
// 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
// 	The apex of a pyramid is the topmost cell of the pyramid. The height of a pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r <= i <= r + h - 1 and c - (i - r) <= j <= c + (i - r).
//
//
// An inverse pyramidal plot of land can be defined as a set of cells with similar criteria:
//
//
// 	The number of cells in the set has to be greater than 1 and all cells must be fertile.
// 	The apex of an inverse pyramid is the bottommost cell of the inverse pyramid. The height of an inverse pyramid is the number of rows it covers. Let (r, c) be the apex of the pyramid, and its height be h. Then, the plot comprises of cells (i, j) where r - h + 1 <= i <= r and c - (r - i) <= j <= c + (r - i).
//
//
// Some examples of valid and invalid pyramidal (and inverse pyramidal) plots are shown below. Black cells indicate fertile cells.
//
// Given a 0-indexed m x n binary matrix grid representing the farmland, return the total number of pyramidal and inverse pyramidal plots that can be found in grid.
//
// Example:
// Input: grid = [[0,1,1,0],[1,1,1,1]]
// Output: 2
// Explanation: The 2 possible pyramidal plots are shown in blue and red respectively.
// There are no inverse pyramidal plots in this grid. 
// Hence total number of pyramidal and inverse pyramidal plots is 2 + 0 = 2.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
//

int countPyramids(int** grid, int gridSize, int* gridColSize) {
    int res = 0;
    int *dpUp = (int*)calloc(*gridColSize, sizeof(int));
    int *dpDown = (int*)calloc(*gridColSize, sizeof(int));
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid[i][j] == 0) {
                dpUp[j] = 0;
            } else {
                int left = (j > 0) ? dpUp[j - 1] : 0;
                int right = (j + 1 < *gridColSize) ? dpUp[j + 1] : 0;
                dpUp[j] = 1 + (left < right ? left : right);
                if (dpUp[j] > 1) res += dpUp[j] - 1;
            }
        }
    }
    for (int i = gridSize - 1; i >= 0; i--) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid[i][j] == 0) {
                dpDown[j] = 0;
            } else {
                int left = (j > 0) ? dpDown[j - 1] : 0;
                int right = (j + 1 < *gridColSize) ? dpDown[j + 1] : 0;
                dpDown[j] = 1 + (left < right ? left : right);
                if (dpDown[j] > 1) res += dpDown[j] - 1;
            }
        }
    }
    free(dpUp);
    free(dpDown);
    return res;     
}
