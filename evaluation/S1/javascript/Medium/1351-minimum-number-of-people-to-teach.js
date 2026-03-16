// Source: https://leetcode.com/problems/minimum-number-of-people-to-teach/   |   Difficulty: Medium
//
// Problem Description:
// On a social network consisting of m users and some friendships between users, two users can communicate with each other if they know a common language.
//
// You are given an integer n, an array languages, and an array friendships where:
//
//
// 	There are n languages numbered 1 through n,
// 	languages[i] is the set of languages the i​​​​​​th​​​​ user knows, and
// 	friendships[i] = [u​​​​​​i​​​, v​​​​​​i] denotes a friendship between the users u​​​​​​​​​​​i​​​​​ and vi.
//
//
// You can choose one language and teach it to some users so that all friends can communicate with each other. Return the minimum number of users you need to teach.
// Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z, this doesn't guarantee that x is a friend of z.
//
// Example:
// Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
// Output: 1
// Explanation: You can either teach user 1 the second language or user 2 the first language.
//
// Constraints:
// 2 <= n <= 500
// 	languages.length == m
// 	1 <= m <= 500
// 	1 <= languages[i].length <= n
// 	1 <= languages[i][j] <= n
// 	1 <= u​​​​​​i < v​​​​​​i <= languages.length
// 	1 <= friendships.length <= 500
// 	All tuples (u​​​​​i, v​​​​​​i) are unique
// 	languages[i] contains only unique values
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} languages
 * @param {number[][]} friendships
 * @return {number}
 */
var minimumTeachings = function(n, languages, friendships) {
	const languageMap = new Map();
	for (let i = 0; i < languages.length; i++) {
		for (const lang of languages[i]) {
			if (!languageMap.has(lang)) {
				languageMap.set(lang, new Set());
			}
			languageMap.get(lang).add(i);
		}
	}

	const friendsToTeach = new Set();
	for (const [u, v] of friendships) {
		const user1Langs = new Set(languages[u - 1]);
		const user2Langs = new Set(languages[v - 1]);
		const canCommunicate = [...user1Langs].some(lang => user2Langs.has(lang));
		if (!canCommunicate) {
			friendsToTeach.add(u - 1);
			friendsToTeach.add(v - 1);
		}
	}

	let minTeachCount = Infinity;
	for (let lang = 1; lang <= n; lang++) {
		let teachCount = 0;
		const speakers = languageMap.get(lang) || new Set();
		for (const friend of friendsToTeach) {
			if (!speakers.has(friend)) {
				teachCount++;
			}
		}
		minTeachCount = Math.min(minTeachCount, teachCount);
	}

	return minTeachCount === Infinity ? 0 : minTeachCount;
};
