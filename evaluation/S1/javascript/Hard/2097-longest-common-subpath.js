// Source: https://leetcode.com/problems/longest-common-subpath/   |   Difficulty: Hard
//
// Problem Description:
// There is a country of n cities numbered from 0 to n - 1. In this country, there is a road connecting every pair of cities.
//
// There are m friends numbered from 0 to m - 1 who are traveling through the country. Each one of them will take a path consisting of some cities. Each path is represented by an integer array that contains the visited cities in order. The path may contain a city more than once, but the same city will not be listed consecutively.
//
// Given an integer n and a 2D integer array paths where paths[i] is an integer array representing the path of the ith friend, return the length of the longest common subpath that is shared by every friend's path, or 0 if there is no common subpath at all.
//
// A subpath of a path is a contiguous sequence of cities within that path.
//
// Example:
// Input: n = 5, paths = [[0,1,2,3,4],
//                        [2,3,4],
//                        [4,0,1,2,3]]
// Output: 2
// Explanation: The longest common subpath is [2,3].
//
// Constraints:
// 1 <= n <= 105
// 	m == paths.length
// 	2 <= m <= 105
// 	sum(paths[i].length) <= 105
// 	0 <= paths[i][j] < n
// 	The same city is not listed multiple times consecutively in paths[i].
//
// Helpful references (internal KB):
// - Substring Search (string, number, hashing, randomized, rolling-hash)
//   • When to use: Use when efficiently finding occurrences of a pattern string within a larger text string, especially for average-case fast string matching. It is suitable for scenarios involving large texts or multiple patterns.
//   • Idea: The Rabin-Karp algorithm finds pattern occurrences in a text by comparing hash values of the pattern and text substrings. It uses a rolling hash function for O(1) substring hash updates, achieving O(N+M) average time complexity and O(NM) worst-case.
//   • Invariants: The pattern's hash value patHash remains constant throughout the search.; At each step i, txtHash accurately represents the hash of txt[i...i+m-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Use a random base for polynomial hashing to enhance collision resistance.
//   • Pitfalls: Hash collisions can lead to false positives, increasing worst-case time.; Improper choice of prime modulus or base can degrade performance.
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} paths
 * @return {number}
 */
var longestCommonSubpath = function(n, paths) {
	if (!paths || paths.length === 0) {
		return 0;
	}

	let minLen = Infinity;
	let maxLen = 0;
	for (const path of paths) {
		minLen = Math.min(minLen, path.length);
		maxLen = Math.max(maxLen, path.length);
	}
	if (minLen === 0) {
		return 0;
	}

	const mod1 = 1000000007n;
	const mod2 = 1000000009n;
	const base = 911382323n;

	const pow1 = new Array(maxLen + 1);
	const pow2 = new Array(maxLen + 1);
	pow1[0] = 1n;
	pow2[0] = 1n;
	for (let i = 1; i <= maxLen; i++) {
		pow1[i] = (pow1[i - 1] * base) % mod1;
		pow2[i] = (pow2[i - 1] * base) % mod2;
	}

	const prefixes = paths.map((path) => {
		const p1 = new Array(path.length + 1);
		const p2 = new Array(path.length + 1);
		p1[0] = 0n;
		p2[0] = 0n;
		for (let i = 0; i < path.length; i++) {
			const v = BigInt(path[i] + 1);
			p1[i + 1] = (p1[i] * base + v) % mod1;
			p2[i + 1] = (p2[i] * base + v) % mod2;
		}
		return { p1, p2, len: path.length };
	});

	const getHashes = (idx, length) => {
		const { p1, p2, len } = prefixes[idx];
		const set = new Set();
		if (length === 0) {
			set.add("0#0");
			return set;
		}
		const pow1Len = pow1[length];
		const pow2Len = pow2[length];
		for (let i = 0; i + length <= len; i++) {
			let h1 = p1[i + length] - (p1[i] * pow1Len) % mod1;
			let h2 = p2[i + length] - (p2[i] * pow2Len) % mod2;
			if (h1 < 0) h1 += mod1;
			if (h2 < 0) h2 += mod2;
			set.add(h1.toString() + "#" + h2.toString());
		}
		return set;
	};

	const hasCommon = (length) => {
		if (length === 0) {
			return true;
		}
		let common = getHashes(0, length);
		if (common.size === 0) {
			return false;
		}
		for (let i = 1; i < prefixes.length; i++) {
			const hashes = getHashes(i, length);
			if (hashes.size === 0) {
				return false;
			}
			const next = new Set();
			for (const key of common) {
				if (hashes.has(key)) {
					next.add(key);
				}
			}
			common = next;
			if (common.size === 0) {
				return false;
			}
		}
		return true;
	};

	let lo = 0;
	let hi = minLen;
	while (lo < hi) {
		const mid = (lo + hi + 1) >> 1;
		if (hasCommon(mid)) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}
	return lo;
};
