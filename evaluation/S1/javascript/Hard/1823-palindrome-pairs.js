// Source: https://leetcode.com/problems/palindrome-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of unique strings words.
//
// A palindrome pair is a pair of integers (i, j) such that:
//
//
//  0 <= i, j < words.length,
//  i != j, and
//  words[i] + words[j] (the concatenation of the two strings) is a palindrome.
//
//
// Return an array of all the palindrome pairs of words.
//
// You must write an algorithm with O(sum of words[i].length) runtime complexity.
//
// Example:
// Input: words = ["abcd","dcba","lls","s","sssll"]
// Output: [[0,1],[1,0],[3,2],[2,4]]
// Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
//
// Constraints:
// 1 <= words.length <= 5000
//  0 <= words[i].length <= 300
//  words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
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
 * @param {string[]} words
 * @return {number[][]}
 */
var palindromePairs = function(words) {
	const root = createNode();

	for (let i = 0; i < words.length; i++) {
		insertWord(root, words[i], i);
	}

	const result = [];
	for (let i = 0; i < words.length; i++) {
		searchWord(root, words[i], i, result);
	}

	return result;
};

function createNode() {
	return {
		next: new Array(26).fill(null),
		wordIndex: -1,
		palSuffixes: []
	};
}

function insertWord(root, word, index) {
	let node = root;
	for (let i = word.length - 1; i >= 0; i--) {
		if (isPalindrome(word, 0, i)) {
			node.palSuffixes.push(index);
		}
		const c = word.charCodeAt(i) - 97;
		if (!node.next[c]) {
			node.next[c] = createNode();
		}
		node = node.next[c];
	}
	node.wordIndex = index;
	node.palSuffixes.push(index);
}

function searchWord(root, word, index, result) {
	let node = root;
	for (let i = 0; i < word.length; i++) {
		if (node.wordIndex >= 0 && node.wordIndex !== index) {
			if (isPalindrome(word, i, word.length - 1)) {
				result.push([index, node.wordIndex]);
			}
		}
		const c = word.charCodeAt(i) - 97;
		if (!node.next[c]) {
			return;
		}
		node = node.next[c];
	}

	for (let k = 0; k < node.palSuffixes.length; k++) {
		const other = node.palSuffixes[k];
		if (other !== index) {
			result.push([index, other]);
		}
	}
}

function isPalindrome(s, left, right) {
	while (left < right) {
		if (s.charCodeAt(left) !== s.charCodeAt(right)) {
			return false;
		}
		left++;
		right--;
	}
	return true;
}
