// Source: https://leetcode.com/problems/longest-duplicate-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or more times. The occurrences may overlap.
//
// Return any duplicated substring that has the longest possible length. If s does not have a duplicated substring, the answer is "".
//
// Example:
// Input: s = "banana"
// Output: "ana"
//
// Constraints:
// 2 <= s.length <= 3 * 104
// 	s consists of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var longestDupSubstring = function(s) {
	const n = s.length;
	if (n <= 1) {
		return '';
	}

	const base = 911382323n;
	const mod1 = 1000000007n;
	const mod2 = 1000000009n;

	const pow1 = new Array(n + 1);
	const pow2 = new Array(n + 1);
	const pref1 = new Array(n + 1);
	const pref2 = new Array(n + 1);
	pow1[0] = 1n;
	pow2[0] = 1n;
	pref1[0] = 0n;
	pref2[0] = 0n;

	for (let i = 0; i < n; i += 1) {
		const code = BigInt(s.charCodeAt(i) - 96);
		pow1[i + 1] = (pow1[i] * base) % mod1;
		pow2[i + 1] = (pow2[i] * base) % mod2;
		pref1[i + 1] = (pref1[i] * base + code) % mod1;
		pref2[i + 1] = (pref2[i] * base + code) % mod2;
	}

	const getHash = (l, r, pref, pow, mod) => {
		let value = pref[r] - (pref[l] * pow[r - l]) % mod;
		if (value < 0n) {
			value += mod;
		}
		return value;
	};

	const check = (len) => {
		if (len === 0) {
			return 0;
		}
		const seen = new Map();
		for (let i = 0; i + len <= n; i += 1) {
			const h1 = getHash(i, i + len, pref1, pow1, mod1);
			const h2 = getHash(i, i + len, pref2, pow2, mod2);
			const key = `${h1}#${h2}`;
			if (seen.has(key)) {
				const positions = seen.get(key);
				for (const start of positions) {
					if (s.slice(start, start + len) === s.slice(i, i + len)) {
						return i;
					}
				}
				positions.push(i);
			} else {
				seen.set(key, [i]);
			}
		}
		return -1;
	};

	let left = 1;
	let right = n - 1;
	let bestLen = 0;
	let bestStart = -1;

	while (left <= right) {
		const mid = Math.floor((left + right) / 2);
		const start = check(mid);
		if (start !== -1) {
			bestLen = mid;
			bestStart = start;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	if (bestStart === -1) {
		return '';
	}
	return s.slice(bestStart, bestStart + bestLen);
};
