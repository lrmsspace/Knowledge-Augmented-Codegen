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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countCoveredBuildings(int n, int[][] buildings) {
        // Create sets to track the presence of buildings in each row and column
        Set<Integer> rows = new HashSet<>();
        Set<Integer> cols = new HashSet<>();

        // Populate the sets with the coordinates of the buildings
        for (int[] building : buildings) {
            rows.add(building[0]);
            cols.add(building[1]);
        }

        int coveredCount = 0;

        // Check each building to see if it is covered
        for (int[] building : buildings) {
            int x = building[0];
            int y = building[1];

            // A building is covered if there are buildings in all four directions
            if (rows.contains(x - 1) && rows.contains(x + 1) && cols.contains(y - 1) && cols.contains(y + 1)) {
                coveredCount++;
            }
        }

        return coveredCount;            
    }
}
