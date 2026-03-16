// Source: https://leetcode.com/problems/count-beautiful-substrings-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a positive integer k.
//
// Let vowels and consonants be the number of vowels and consonants in a string.
//
// A string is beautiful if:
//
//
// 	vowels == consonants.
// 	(vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is divisible by k.
//
//
// Return the number of non-empty beautiful substrings in the given string s.
//
// A substring is a contiguous sequence of characters in a string.
//
// Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
//
// Consonant letters in English are every letter except vowels.
//
// Example:
// Input: s = "baeyh", k = 2
// Output: 2
// Explanation: There are 2 beautiful substrings in the given string.
// - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["y","h"]).
// You can see that string "aeyh" is beautiful as vowels == consonants and vowels * consonants % k == 0.
// - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["b","y"]).
// You can see that string "baey" is beautiful as vowels == consonants and vowels * consonants % k == 0.
// It can be shown that there are only 2 beautiful substrings in the given string.
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	1 <= k <= 1000
// 	s consists of only English lowercase letters.
//
// Helpful references (internal KB):
// - Suffix array (array, string, suffix-array, divide-and-conquer, recursion)
//   • When to use: Use when you need to efficiently perform various string operations like pattern searching, finding repeated substrings, or comparing suffixes lexicographically on a given text. It is a fundamental data structure for advanced string algorithms.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string. It allows for efficient string operations, with construction typically achievable in O(N log N) or O(N) time for advanced algorithms.
//   • Invariants: The suffix array SA[i] stores the starting index of the i-th lexicographically smallest suffix.; All suffixes of the input string are present exactly once in the suffix array.
//   • Tips: Consider using SA-IS for optimal O(N) construction time and space complexity.; Pair the suffix array with an LCP array for enhanced functionality, such as finding longest common substrings.
//   • Pitfalls: Naive O(N^2 log N) construction is too slow for large input strings.; Implementing linear-time algorithms like SA-IS or DC3 can be complex and error-prone.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
 * @param {number} k
 * @return {number}
 */
var beautifulSubstrings = function(s, k) {
	var n = s.length;
	var count = 0;

	// Precompute prefix counts of vowels and consonants.
	var prefix_vowels = new Array(n + 1).fill(0);
	var prefix_consonants = new Array(n + 1).fill(0);

	for (var i = 0; i < n; i++) {
		prefix_vowels[i + 1] = prefix_vowels[i] + (isVowel(s[i]) ? 1 : 0);
		prefix_consonants[i + 1] = prefix_consonants[i] + (isVowel(s[i]) ? 0 : 1);
	}

	// Check all substrings using the prefix counts.
	for (var start = 0; start < n; start++) {
		for (var end = start; end < n; end++) {
			var vowels = prefix_vowels[end + 1] - prefix_vowels[start];
			var consonants = prefix_consonants[end + 1] - prefix_consonants[start];

			if (vowels === consonants && (vowels * consonants) % k === 0) {
				count++;
			}
		}
	}

	return count;
};
