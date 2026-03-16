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

/**
 * @param {number} n
 * @param {number[][]} buildings
 * @return {number}
 */
var countCoveredBuildings = function(n, buildings) {
    const buildingSet = new Set(buildings.map(([x, y]) => `${x},${y}`));
    let coveredCount = 0;
    for (const [x, y] of buildings) {
        if (
            buildingSet.has(`${x - 1},${y}`) &&
            buildingSet.has(`${x + 1},${y}`) &&
            buildingSet.has(`${x},${y - 1}`) &&
            buildingSet.has(`${x},${y + 1}`)
        ) {
            coveredCount++;
        }
    }
    return coveredCount;
};