// Source: https://leetcode.com/problems/permutation-in-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
//
// In other words, return true if one of s1's permutations is the substring of s2.
//
// Example:
// Input: s1 = "ab", s2 = "eidbaooo"
// Output: true
// Explanation: s2 contains one permutation of s1 ("ba").
//
// Constraints:
// 1 <= s1.length, s2.length <= 104
// 	s1 and s2 consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Substring Search (string, number, hashing, randomized, rolling-hash)
//   • When to use: Use when efficiently finding occurrences of a pattern string within a larger text string, especially for average-case fast string matching. It is suitable for scenarios involving large texts or multiple patterns.
//   • Idea: The Rabin-Karp algorithm finds pattern occurrences in a text by comparing hash values of the pattern and text substrings. It uses a rolling hash function for O(1) substring hash updates, achieving O(N+M) average time complexity and O(NM) worst-case.
//   • Invariants: The pattern's hash value patHash remains constant throughout the search.; At each step i, txtHash accurately represents the hash of txt[i...i+m-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Use a random base for polynomial hashing to enhance collision resistance.
//   • Pitfalls: Hash collisions can lead to false positives, increasing worst-case time.; Improper choice of prime modulus or base can degrade performance.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
var checkInclusion = function(s1, s2) {
	const count1 = new Array(26).fill(0);
	const count2 = new Array(26).fill(0);
	const aCharCode = 'a'.charCodeAt(0);

	for (const char of s1) {
		count1[char.charCodeAt(0) - aCharCode]++;
	}

	for (let i = 0; i < s2.length; i++) {
		count2[s2.charCodeAt(i) - aCharCode]++;

		if (i >= s1.length) {
			count2[s2.charCodeAt(i - s1.length) - aCharCode]--;
		}

		if (arraysEqual(count1, count2)) {
			return true;
		}
	}

	return false;
};
