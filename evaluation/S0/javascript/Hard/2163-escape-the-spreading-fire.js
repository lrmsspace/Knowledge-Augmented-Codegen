// Source: https://leetcode.com/problems/escape-the-spreading-fire/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three values:
//
//
// 	0 represents grass,
// 	1 represents fire,
// 	2 represents a wall that you and fire cannot pass through.
//
//
// You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, (m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all adjacent cells that are not walls.
//
// Return the maximum number of minutes that you can stay in your initial position before moving while still safely reaching the safehouse. If this is impossible, return -1. If you can always reach the safehouse regardless of the minutes stayed, return 109.
//
// Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse.
//
// A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
// Example:
// Input: grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
// Output: 3
// Explanation: The figure above shows the scenario where you stay in the initial position for 3 minutes.
// You will still be able to safely reach the safehouse.
// Staying for more than 3 minutes will not allow you to safely reach the safehouse.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 300
// 	4 <= m * n <= 2 * 104
// 	grid[i][j] is either 0, 1, or 2.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maximumMinutes = function(grid) {
	const m = grid.length;
	const n = grid[0].length;
	const INF = Number.MAX_SAFE_INTEGER;
	const dirs = [
		[1, 0],
		[-1, 0],
		[0, 1],
		[0, -1]
	];

	const fireTime = Array.from({ length: m }, () => Array(n).fill(INF));
	const qx = [];
	const qy = [];
	const qt = [];
	let head = 0;

	for (let i = 0; i < m; i++) {
		for (let j = 0; j < n; j++) {
			if (grid[i][j] === 2) {
				fireTime[i][j] = -1;
			} else if (grid[i][j] === 1) {
				fireTime[i][j] = 0;
				qx.push(i);
				qy.push(j);
				qt.push(0);
			}
		}
	}

	while (head < qx.length) {
		const x = qx[head];
		const y = qy[head];
		const t = qt[head];
		head++;

		for (const [dx, dy] of dirs) {
			const nx = x + dx;
			const ny = y + dy;
			if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
			if (grid[nx][ny] === 2) continue;
			if (t + 1 < fireTime[nx][ny]) {
				fireTime[nx][ny] = t + 1;
				qx.push(nx);
				qy.push(ny);
				qt.push(t + 1);
			}
		}
	}

	const canEscape = (wait) => {
		const startFire = fireTime[0][0];
		if (startFire !== INF && wait >= startFire) return false;

		const visited = Array.from({ length: m }, () => Array(n).fill(false));
		const bx = [0];
		const by = [0];
		const bt = [wait];
		let bhead = 0;
		visited[0][0] = true;

		while (bhead < bx.length) {
			const x = bx[bhead];
			const y = by[bhead];
			const t = bt[bhead];
			bhead++;

			if (x === m - 1 && y === n - 1) return true;

			for (const [dx, dy] of dirs) {
				const nx = x + dx;
				const ny = y + dy;
				if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
				if (grid[nx][ny] === 2) continue;
				if (visited[nx][ny]) continue;

				const nt = t + 1;
				const ft = fireTime[nx][ny];

				if (nx === m - 1 && ny === n - 1) {
					if (ft === INF || nt <= ft) {
						visited[nx][ny] = true;
						bx.push(nx);
						by.push(ny);
						bt.push(nt);
					}
				} else {
					if (ft === INF || nt < ft) {
						visited[nx][ny] = true;
						bx.push(nx);
						by.push(ny);
						bt.push(nt);
					}
				}
			}
		}

		return false;
	};

	if (!canEscape(0)) return -1;
	const LIMIT = 1000000000;
	if (canEscape(LIMIT)) return LIMIT;

	let low = 0;
	let high = LIMIT;
	while (low < high) {
		const mid = Math.floor((low + high + 1) / 2);
		if (canEscape(mid)) {
			low = mid;
		} else {
			high = mid - 1;
		}
	}
	return low;
};
