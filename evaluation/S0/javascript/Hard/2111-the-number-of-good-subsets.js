// Source: https://leetcode.com/problems/the-number-of-good-subsets/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. We call a subset of nums good if its product can be represented as a product of one or more distinct prime numbers.
//
//
// 	For example, if nums = [1, 2, 3, 4]:
//
// 	
// 		[2, 3], [1, 2, 3], and [1, 3] are good subsets with products 6 = 2*3, 6 = 2*3, and 3 = 3 respectively.
// 		[1, 4] and [4] are not good subsets with products 4 = 2*2 and 4 = 2*2 respectively.
// 	
// 	
//
//
// Return the number of different good subsets in nums modulo 109 + 7.
//
// A subset of nums is any array that can be obtained by deleting some (possibly none or all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 6
// Explanation: The good subsets are:
// - [1,2]: product is 2, which is the product of distinct prime 2.
// - [1,2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [1,3]: product is 3, which is the product of distinct prime 3.
// - [2]: product is 2, which is the product of distinct prime 2.
// - [2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [3]: product is 3, which is the product of distinct prime 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 30
//

/**
 * @param {number[]} nums
 * @return {number}
 */
    
 var numberOfGoodSubsets = function(nums) {
	const MOD = 1000000007;
	const primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29];
	const counts = new Array(31).fill(0);

	for (const value of nums) {
		counts[value] += 1;
	}

	const masks = new Array(31).fill(0);
	for (let value = 2; value <= 30; value += 1) {
		let x = value;
		let mask = 0;
		let squareFree = true;

		for (let i = 0; i < primes.length; i += 1) {
			const prime = primes[i];
			if (prime * prime > x) {
				break;
			}
			if (x % prime === 0) {
				let count = 0;
				while (x % prime === 0) {
					x = Math.floor(x / prime);
					count += 1;
				}
				if (count > 1) {
					squareFree = false;
					break;
				}
				mask |= 1 << i;
			}
		}

		if (squareFree) {
			if (x > 1) {
				const idx = primes.indexOf(x);
				if (idx >= 0) {
					mask |= 1 << idx;
				}
			}
			masks[value] = mask;
		} else {
			masks[value] = 0;
		}
	}

	const dp = new Array(1 << primes.length).fill(0);
	dp[0] = 1;

	for (let value = 2; value <= 30; value += 1) {
		const count = counts[value];
		if (count === 0) {
			continue;
		}
		const mask = masks[value];
		if (mask === 0) {
			continue;
		}

		const next = dp.slice();
		for (let state = 0; state < dp.length; state += 1) {
			if ((state & mask) !== 0) {
				continue;
			}
			const combined = state | mask;
			const add = (dp[state] * count) % MOD;
			next[combined] = (next[combined] + add) % MOD;
		}
		for (let i = 0; i < dp.length; i += 1) {
			dp[i] = next[i];
		}
	}

	let result = 0;
	for (let state = 1; state < dp.length; state += 1) {
		result = (result + dp[state]) % MOD;
	}

	const ones = counts[1];
	let pow2 = 1;
	for (let i = 0; i < ones; i += 1) {
		pow2 = (pow2 * 2) % MOD;
	}

	return (result * pow2) % MOD;
 };