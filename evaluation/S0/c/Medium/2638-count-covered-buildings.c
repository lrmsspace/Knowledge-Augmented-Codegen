// Source: https://leetcode.com/problems/count-covered-buildings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n, representing an n x n city. You are also given a 2D grid buildings, where buildings[i] = [x, y] denotes a unique building located at coordinates [x, y].
//
// A building is covered if there is at least one building in all four directions: left, right, above, and below.
//
// Return the number of covered buildings.
//
// Example:
// Input: n = 3, buildings = [[1,2],[2,2],[3,2],[2,1],[2,3]]
//
// Output: 1
//
// Explanation:
//
//
// 	Only building [2,2] is covered as it has at least one building:
//
// 	
// 		above ([1,2])
// 		below ([3,2])
// 		left ([2,1])
// 		right ([2,3])
// 	
// 	
// 	Thus, the count of covered buildings is 1.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= buildings.length <= 105 
// 	buildings[i] = [x, y]
// 	1 <= x, y <= n
// 	All coordinates of buildings are unique.
//

int countCoveredBuildings(int n, int** buildings, int buildingsSize, int* buildingsColSize) {
    int count = 0;
    int *rowMin = (int *)malloc((n + 1) * sizeof(int));
    int *rowMax = (int *)malloc((n + 1) * sizeof(int));
    int *colMin = (int *)malloc((n + 1) * sizeof(int));
    int *colMax = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        rowMin[i] = n + 1;
        rowMax[i] = 0;
        colMin[i] = n + 1;
        colMax[i] = 0;
    }

    for (int i = 0; i < buildingsSize; i++) {
        int x = buildings[i][0];
        int y = buildings[i][1];

        if (y < rowMin[x]) rowMin[x] = y;
        if (y > rowMax[x]) rowMax[x] = y;
        if (x < colMin[y]) colMin[y] = x;
        if (x > colMax[y]) colMax[y] = x;
    }

    for (int i = 0; i < buildingsSize; i++) {
        int x = buildings[i][0];
        int y = buildings[i][1];

        if (y > rowMin[x] && y < rowMax[x] && x > colMin[y] && x < colMax[y]) {
            count++;
        }
    }

    free(rowMin);
    free(rowMax);
    free(colMin);
    free(colMax);

    return count;       
}
