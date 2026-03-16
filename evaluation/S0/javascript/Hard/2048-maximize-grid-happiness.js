// Source: https://leetcode.com/problems/maximize-grid-happiness/   |   Difficulty: Hard
//
// Problem Description:
// You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.
//
// You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.
//
// The happiness of each person is calculated as follows:
//
//
// 	Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
// 	Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
//
//
// Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.
//
// The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.
//
// Example:
// Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
// Output: 240
// Explanation: Assume the grid is 1-indexed with coordinates (row, column).
// We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
// - Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
// - Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
// - Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
// The grid happiness is 120 + 60 + 60 = 240.
// The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.
//
// Constraints:
// 1 <= m, n <= 5
// 	0 <= introvertsCount, extrovertsCount <= min(m * n, 6)
//

/**
 * @param {number} m
 * @param {number} n
 * @param {number} introvertsCount
 * @param {number} extrovertsCount
 * @return {number}
 */
var getMaxGridHappiness = function(m, n, introvertsCount, extrovertsCount) {
	const baseHappy = [0, 120, 40];
	const delta = [
		[0, 0, 0],
		[0, -60, -10],
		[0, -10, 40]
	];

	const totalStates = Math.pow(3, n);
	const introCount = new Array(totalStates).fill(0);
	const extroCount = new Array(totalStates).fill(0);
	const innerScore = new Array(totalStates).fill(0);
	const digits = Array.from({ length: totalStates }, () => new Array(n).fill(0));

	for (let mask = 0; mask < totalStates; mask += 1) {
		let temp = mask;
		let score = 0;
		let prev = 0;
		for (let i = 0; i < n; i += 1) {
			const cur = temp % 3;
			digits[mask][i] = cur;
			temp = Math.floor(temp / 3);
			if (cur === 1) {
				introCount[mask] += 1;
			} else if (cur === 2) {
				extroCount[mask] += 1;
			}
			score += baseHappy[cur];
			if (i > 0) {
				score += delta[cur][prev];
			}
			prev = cur;
		}
		innerScore[mask] = score;
	}

	let dp = new Array(totalStates).fill(null).map(() => {
		return new Array(introvertsCount + 1).fill(null).map(() => {
			return new Array(extrovertsCount + 1).fill(-Infinity);
		});
	});
	dp[0][0][0] = 0;

	for (let row = 0; row < m; row += 1) {
		const next = new Array(totalStates).fill(null).map(() => {
			return new Array(introvertsCount + 1).fill(null).map(() => {
				return new Array(extrovertsCount + 1).fill(-Infinity);
			});
		});

		for (let prevMask = 0; prevMask < totalStates; prevMask += 1) {
			for (let i = 0; i <= introvertsCount; i += 1) {
				for (let e = 0; e <= extrovertsCount; e += 1) {
					const baseVal = dp[prevMask][i][e];
					if (baseVal === -Infinity) {
						continue;
					}
					for (let curMask = 0; curMask < totalStates; curMask += 1) {
						const i2 = i + introCount[curMask];
						const e2 = e + extroCount[curMask];
						if (i2 > introvertsCount || e2 > extrovertsCount) {
							continue;
						}
						let add = innerScore[curMask];
						for (let c = 0; c < n; c += 1) {
							add += delta[digits[curMask][c]][digits[prevMask][c]];
						}
						const candidate = baseVal + add;
						if (candidate > next[curMask][i2][e2]) {
							next[curMask][i2][e2] = candidate;
						}
					}
				}
			}
		}
		dp = next;
	}

	let best = 0;
	for (let mask = 0; mask < totalStates; mask += 1) {
		for (let i = 0; i <= introvertsCount; i += 1) {
			for (let e = 0; e <= extrovertsCount; e += 1) {
				if (dp[mask][i][e] > best) {
					best = dp[mask][i][e];
				}
			}
		}
	}

	return best;
};
