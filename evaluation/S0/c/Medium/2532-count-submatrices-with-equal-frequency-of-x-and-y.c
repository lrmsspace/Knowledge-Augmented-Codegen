// Source: https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:
//
//
// 	grid[0][0]
// 	an equal frequency of 'X' and 'Y'.
// 	at least one 'X'.
//
// Example:
// Input: grid = [["X","Y","."],["Y",".","."]]
//
// Output: 3
//
// Explanation:
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 1000
// 	grid[i][j] is either 'X', 'Y', or '.'.
//

int numberOfSubmatrices(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int result = 0;

    for (int top = 0; top < m; top++) {
        int countX[n];
        int countY[n];
        memset(countX, 0, sizeof(countX));
        memset(countY, 0, sizeof(countY));

        for (int bottom = top; bottom < m; bottom++) {
            for (int col = 0; col < n; col++) {
                if (grid[bottom][col] == 'X') {
                    countX[col]++;
                } else if (grid[bottom][col] == 'Y') {
                    countY[col]++;
                }
            }

            // Hash map to store frequency differences
            #define HASH_SIZE 20011
            int hashMap[HASH_SIZE];
            memset(hashMap, 0, sizeof(hashMap));
            int diff = 0;
            hashMap[10000] = 1; // Offset to handle negative indices

            for (int col = 0; col < n; col++) {
                if (countX[col] > 0) {
                    diff += (countX[col] - countY[col]);
                } else if (countY[col] > 0) {
                    diff -= (countY[col] - countX[col]);
                }

                int hashIndex = diff + 10000;
                result += hashMap[hashIndex];
                hashMap[hashIndex]++;
            }
        }
    }

    return result;
}
