// Source: https://leetcode.com/problems/sum-of-total-strength-of-wizards/   |   Difficulty: Hard
//
// Problem Description:
// As the ruler of a kingdom, you have an army of wizards at your command.
//
// You are given a 0-indexed integer array strength, where strength[i] denotes the strength of the ith wizard. For a contiguous group of wizards (i.e. the wizards' strengths form a subarray of strength), the total strength is defined as the product of the following two values:
//
//
// 	The strength of the weakest wizard in the group.
// 	The total of all the individual strengths of the wizards in the group.
//
//
// Return the sum of the total strengths of all contiguous groups of wizards. Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: strength = [1,3,1,2]
// Output: 44
// Explanation: The following are all the contiguous groups of wizards:
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [3] from [1,3,1,2] has a total strength of min([3]) * sum([3]) = 3 * 3 = 9
// - [1] from [1,3,1,2] has a total strength of min([1]) * sum([1]) = 1 * 1 = 1
// - [2] from [1,3,1,2] has a total strength of min([2]) * sum([2]) = 2 * 2 = 4
// - [1,3] from [1,3,1,2] has a total strength of min([1,3]) * sum([1,3]) = 1 * 4 = 4
// - [3,1] from [1,3,1,2] has a total strength of min([3,1]) * sum([3,1]) = 1 * 4 = 4
// - [1,2] from [1,3,1,2] has a total strength of min([1,2]) * sum([1,2]) = 1 * 3 = 3
// - [1,3,1] from [1,3,1,2] has a total strength of min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
// - [3,1,2] from [1,3,1,2] has a total strength of min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
// - [1,3,1,2] from [1,3,1,2] has a total strength of min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
// The sum of all the total strengths is 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44.
//
// Constraints:
// 1 <= strength.length <= 105
// 	1 <= strength[i] <= 109
//

/**
 * @param {number[]} strength
 * @return {number}
 */
var totalStrength = function(strength) {
	const MOD = 1000000007n;
	const n = strength.length;
	const arr = new Array(n);
	for (let i = 0; i < n; i++) {
		arr[i] = BigInt(strength[i]);
	}

	// prefix sums and prefix of prefix sums
	const prefix = new Array(n + 1).fill(0n);
	for (let i = 0; i < n; i++) {
		prefix[i + 1] = (prefix[i] + arr[i]) % MOD;
	}
	const prefix2 = new Array(n + 2).fill(0n);
	for (let i = 0; i <= n; i++) {
		prefix2[i + 1] = (prefix2[i] + prefix[i]) % MOD;
	}

	// Previous strictly smaller and next smaller or equal
	const left = new Array(n).fill(-1);
	const right = new Array(n).fill(n);
	const stack = [];
	for (let i = 0; i < n; i++) {
		while (stack.length && arr[stack[stack.length - 1]] >= arr[i]) {
			const idx = stack.pop();
			right[idx] = i;
		}
		left[i] = stack.length ? stack[stack.length - 1] : -1;
		stack.push(i);
	}

	let ans = 0n;
	for (let i = 0; i < n; i++) {
		const l = left[i];
		const r = right[i];
		const leftCount = BigInt(i - l);
		const rightCount = BigInt(r - i);

		// Sum of prefix sums on [i+1, r] and [l+1, i]
		const sumRight = (prefix2[r + 1] - prefix2[i + 1] + MOD) % MOD;
		const sumLeft = (prefix2[i + 1] - prefix2[l + 1] + MOD) % MOD;

		const contrib = (arr[i] % MOD) * ((sumRight * leftCount - sumLeft * rightCount) % MOD);
		ans = (ans + contrib) % MOD;
	}

	ans = (ans + MOD) % MOD;
	return Number(ans);
};
