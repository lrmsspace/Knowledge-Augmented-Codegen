// Source: https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/   |   Difficulty: Hard
//
// Problem Description:
// You are given positive integers low, high, and k.
//
// A number is beautiful if it meets both of the following conditions:
//
//
// 	The count of even digits in the number is equal to the count of odd digits.
// 	The number is divisible by k.
//
//
// Return the number of beautiful integers in the range [low, high].
//
// Example:
// Input: low = 10, high = 20, k = 3
// Output: 2
// Explanation: There are 2 beautiful integers in the given range: [12,18]. 
// - 12 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// - 18 is beautiful because it contains 1 odd digit and 1 even digit, and is divisible by k = 3.
// Additionally we can see that:
// - 16 is not beautiful because it is not divisible by k = 3.
// - 15 is not beautiful because it does not contain equal counts even and odd digits.
// It can be shown that there are only 2 beautiful integers in the given range.
//
// Constraints:
// 0 < low <= high <= 109
// 	0 < k <= 20
//

/**
 * @param {number} low
 * @param {number} high
 * @param {number} k
 * @return {number}
 */ 
 var numberOfBeautifulIntegers = function(low, high, k) {
	const countUpTo = (n) => {
		if (n <= 0) {
			return 0;
		}

		const digits = String(n).split("").map(Number);
		const memo = new Map();

		const dfs = (idx, mod, balance, started, tight) => {
			if (idx === digits.length) {
				if (!started) {
					return 0;
				}
				return balance === 0 && mod === 0 ? 1 : 0;
			}

			if (!tight) {
				const key = `${idx}|${mod}|${balance}|${started ? 1 : 0}`;
				if (memo.has(key)) {
					return memo.get(key);
				}
			}

			const limit = tight ? digits[idx] : 9;
			let total = 0;

			for (let d = 0; d <= limit; d++) {
				const nextTight = tight && d === limit;
				const nextStarted = started || d !== 0;
				let nextMod = mod;
				let nextBalance = balance;

				if (nextStarted) {
					nextMod = (mod * 10 + d) % k;
					nextBalance += d % 2 === 0 ? 1 : -1;
				}

				total += dfs(idx + 1, nextMod, nextBalance, nextStarted, nextTight);
			}

			if (!tight) {
				const key = `${idx}|${mod}|${balance}|${started ? 1 : 0}`;
				memo.set(key, total);
			}

			return total;
		};

		return dfs(0, 0, 0, false, true);
	};

	return countUpTo(high) - countUpTo(low - 1);
 };
 