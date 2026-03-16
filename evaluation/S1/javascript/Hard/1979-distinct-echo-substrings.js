// Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
//
// Example:
// Input: text = "abcabcabc"
// Output: 3
// Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
//
// Constraints:
// 1 <= text.length <= 2000
// 	text has only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} text
 * @return {number}
 */
var distinctEchoSubstrings = function(text) {
	var n = text.length;
	if (n < 2) {
		return 0;
	}

	var base = 911382323n;
	var mod1 = 1000000007n;
	var mod2 = 1000000009n;

	var pow1 = new Array(n + 1);
	var pow2 = new Array(n + 1);
	var pre1 = new Array(n + 1);
	var pre2 = new Array(n + 1);
	pow1[0] = 1n;
	pow2[0] = 1n;
	pre1[0] = 0n;
	pre2[0] = 0n;

	for (var i = 0; i < n; i++) {
		var code = BigInt(text.charCodeAt(i) - 96);
		pow1[i + 1] = (pow1[i] * base) % mod1;
		pow2[i + 1] = (pow2[i] * base) % mod2;
		pre1[i + 1] = (pre1[i] * base + code) % mod1;
		pre2[i + 1] = (pre2[i] * base + code) % mod2;
	}

	var getHash = function(pre, pow, mod, l, r) {
		var res = pre[r] - (pre[l] * pow[r - l]) % mod;
		if (res < 0n) {
			res += mod;
		}
		return res;
	};

	var seen = new Set();

	for (var len = 1; len * 2 <= n; len++) {
		for (var start = 0; start + 2 * len <= n; start++) {
			var mid = start + len;
			var end = start + 2 * len;

			var h1a = getHash(pre1, pow1, mod1, start, mid);
			var h1b = getHash(pre1, pow1, mod1, mid, end);
			if (h1a !== h1b) {
				continue;
			}

			var h2a = getHash(pre2, pow2, mod2, start, mid);
			var h2b = getHash(pre2, pow2, mod2, mid, end);
			if (h2a !== h2b) {
				continue;
			}

			var full1 = getHash(pre1, pow1, mod1, start, end);
			var full2 = getHash(pre2, pow2, mod2, start, end);
			seen.add(String(full1) + "," + String(full2));
		}
	}

	return seen.size;
};
