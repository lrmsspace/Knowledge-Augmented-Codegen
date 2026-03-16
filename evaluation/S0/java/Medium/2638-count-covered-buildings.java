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

class Solution {
    public int countCoveredBuildings(int n, int[][] buildings) {
        boolean[] rowHasBuilding = new boolean[n + 1];
        boolean[] colHasBuilding = new boolean[n + 1];

        for (int[] building : buildings) {
            int x = building[0];
            int y = building[1];
            rowHasBuilding[x] = true;
            colHasBuilding[y] = true;
        }

        int coveredCount = 0;

        for (int[] building : buildings) {
            int x = building[0];
            int y = building[1];

            if (hasBuildingInAllDirections(x, y, rowHasBuilding, colHasBuilding)) {
                coveredCount++;
            }
        }

        return coveredCount;            
    }
}
