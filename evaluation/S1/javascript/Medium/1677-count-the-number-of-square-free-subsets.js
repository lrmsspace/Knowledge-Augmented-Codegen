// Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer 0-indexed array nums.
//
// A subset of the array nums is square-free if the product of its elements is a square-free integer.
//
// A square-free integer is an integer that is divisible by no square number other than 1.
//
// Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
//
// A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [3,4,4,5]
// Output: 3
// Explanation: There are 3 square-free subsets in this example:
// - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
// - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
// - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
// It can be proven that there are no more than 3 square-free subsets in the given array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 30
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var squareFreeSubsets = function(nums) {
	var MOD = 1000000007;
	var primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29];
	var maxMask = 1 << primes.length;

	var freq = new Array(31).fill(0);
	for (var i = 0; i < nums.length; i++) {
		freq[nums[i]]++;
	}

	var masks = new Array(31).fill(-1);
	masks[1] = 0;
	for (var v = 2; v <= 30; v++) {
		var x = v;
		var mask = 0;
		var valid = true;
		for (var p = 0; p < primes.length; p++) {
			var prime = primes[p];
			var count = 0;
			while (x % prime === 0) {
				x = Math.floor(x / prime);
				count++;
			}
			if (count >= 2) {
				valid = false;
				break;
			}
			if (count === 1) {
				mask |= 1 << p;
			}
		}
		masks[v] = valid ? mask : -1;
	}

	var dp = new Array(maxMask).fill(0);
	dp[0] = 1;

	for (var val = 2; val <= 30; val++) {
		var countVal = freq[val];
		var valMask = masks[val];
		if (countVal === 0 || valMask === -1) {
			continue;
		}

		var next = dp.slice();
		for (var maskIdx = 0; maskIdx < maxMask; maskIdx++) {
			if ((maskIdx & valMask) !== 0) {
				continue;
			}
			var combined = maskIdx | valMask;
			var add = (dp[maskIdx] * countVal) % MOD;
			next[combined] = (next[combined] + add) % MOD;
		}
		dp = next;
	}

	var total = 0;
	for (var m = 0; m < maxMask; m++) {
		total = (total + dp[m]) % MOD;
	}

	var ones = freq[1];
	var pow2 = 1;
	var base = 2;
	var exp = ones;
	while (exp > 0) {
		if (exp & 1) {
			pow2 = (pow2 * base) % MOD;
		}
		base = (base * base) % MOD;
		exp = Math.floor(exp / 2);
	}

	total = (total * pow2) % MOD;
	total = (total - 1 + MOD) % MOD;
	return total;
};
