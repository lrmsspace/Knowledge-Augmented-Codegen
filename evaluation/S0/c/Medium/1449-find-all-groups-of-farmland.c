// Source: https://leetcode.com/problems/find-all-groups-of-farmland/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix land where a 0 represents a hectare of forested land and a 1 represents a hectare of farmland.
//
// To keep the land organized, there are designated rectangular areas of hectares that consist entirely of farmland. These rectangular areas are called groups. No two groups are adjacent, meaning farmland in one group is not four-directionally adjacent to another farmland in a different group.
//
// land can be represented by a coordinate system where the top left corner of land is (0, 0) and the bottom right corner of land is (m-1, n-1). Find the coordinates of the top left and bottom right corner of each group of farmland. A group of farmland with a top left corner at (r1, c1) and a bottom right corner at (r2, c2) is represented by the 4-length array [r1, c1, r2, c2].
//
// Return a 2D array containing the 4-length arrays described above for each group of farmland in land. If there are no groups of farmland, return an empty array. You may return the answer in any order.
//
// Example:
// Input: land = [[1,0,0],[0,1,1],[0,1,1]]
// Output: [[0,0,0,0],[1,1,2,2]]
// Explanation:
// The first group has a top left corner at land[0][0] and a bottom right corner at land[0][0].
// The second group has a top left corner at land[1][1] and a bottom right corner at land[2][2].
//
// Constraints:
// m == land.length
// 	n == land[i].length
// 	1 <= m, n <= 300
// 	land consists of only 0's and 1's.
// 	Groups of farmland are rectangular in shape.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findFarmland(int** land, int landSize, int* landColSize, int* returnSize, int** returnColumnSizes) {
    int maxGroups = landSize * (*landColSize) / 2; // Maximum possible groups
    int** result = (int**)malloc(maxGroups * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxGroups * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < landSize; i++) {
        for (int j = 0; j < *landColSize; j++) {
            if (land[i][j] == 1) {
                int r1 = i, c1 = j;
                int r2 = i, c2 = j;

                // Find the bottom-right corner of the farmland group
                while (r2 + 1 < landSize && land[r2 + 1][j] == 1) {
                    r2++;
                }
                while (c2 + 1 < *landColSize && land[i][c2 + 1] == 1) {
                    c2++;
                }

                // Mark the farmland as visited
                for (int x = r1; x <= r2; x++) {
                    for (int y = c1; y <= c2; y++) {
                        land[x][y] = 0;
                    }
                }

                // Store the result
                result[*returnSize] = (int*)malloc(4 * sizeof(int));
                result[*returnSize][0] = r1;
                result[*returnSize][1] = c1;
                result[*returnSize][2] = r2;
                result[*returnSize][3] = c2;
                (*returnColumnSizes)[*returnSize] = 4;
                (*returnSize)++;
            }
        }
    }

    return result;      
}
