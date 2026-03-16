// Source: https://leetcode.com/problems/contain-virus/   |   Difficulty: Hard
//
// Problem Description:
// A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.
//
// The world is modeled as an m x n binary grid isInfected, where isInfected[i][j] == 0 represents uninfected cells, and isInfected[i][j] == 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.
//
// Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region (i.e., the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night). There will never be a tie.
//
// Return the number of walls used to quarantine all the infected regions. If the world will become fully infected, return the number of walls used.
//
// Example:
// Input: isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
// Output: 10
// Explanation: There are 2 contaminated regions.
// On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:
//
// On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
//
// Constraints:
// m == isInfected.length
// 	n == isInfected[i].length
// 	1 <= m, n <= 50
// 	isInfected[i][j] is either 0 or 1.
// 	There is always a contiguous viral region throughout the described process that will infect strictly more uncontaminated squares in the next round.
//

/**
 * @param {number[][]} isInfected
 * @return {number}
 */
var containVirus = function(isInfected) {
	var m = isInfected.length;
	var n = isInfected[0].length;
	var dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]];
	var totalWalls = 0;

	while (true) {
		var visited = Array.from({ length: m }, function() {
			return Array(n).fill(false);
		});
		var regions = [];
		var frontiers = [];
		var wallsNeeded = [];

		for (var r = 0; r < m; r++) {
			for (var c = 0; c < n; c++) {
				if (isInfected[r][c] !== 1 || visited[r][c]) {
					continue;
				}

				var region = [];
				var frontier = new Set();
				var walls = 0;
				var stack = [[r, c]];
				visited[r][c] = true;

				while (stack.length > 0) {
					var cell = stack.pop();
					var cr = cell[0];
					var cc = cell[1];
					region.push([cr, cc]);

					for (var d = 0; d < 4; d++) {
						var nr = cr + dirs[d][0];
						var nc = cc + dirs[d][1];
						if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
							continue;
						}
						if (isInfected[nr][nc] === 0) {
							walls += 1;
							frontier.add(nr + "," + nc);
						} else if (isInfected[nr][nc] === 1 && !visited[nr][nc]) {
							visited[nr][nc] = true;
							stack.push([nr, nc]);
						}
					}
				}

				regions.push(region);
				frontiers.push(frontier);
				wallsNeeded.push(walls);
			}
		}

		if (regions.length === 0) {
			break;
		}

		var maxIndex = -1;
		var maxFrontierSize = 0;
		for (var i = 0; i < frontiers.length; i++) {
			if (frontiers[i].size > maxFrontierSize) {
				maxFrontierSize = frontiers[i].size;
				maxIndex = i;
			}
		}

		if (maxFrontierSize === 0) {
			break;
		}

		totalWalls += wallsNeeded[maxIndex];

		for (var qi = 0; qi < regions[maxIndex].length; qi++) {
			var qcell = regions[maxIndex][qi];
			isInfected[qcell[0]][qcell[1]] = 2;
		}

		for (var ri = 0; ri < regions.length; ri++) {
			if (ri === maxIndex) {
				continue;
			}
			frontiers[ri].forEach(function(key) {
				var parts = key.split(",");
				var fr = parseInt(parts[0], 10);
				var fc = parseInt(parts[1], 10);
				if (isInfected[fr][fc] === 0) {
					isInfected[fr][fc] = 1;
				}
			});
		}
	}

	return totalWalls;
};
