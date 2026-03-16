// Source: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/   |   Difficulty: Medium
//
// Problem Description:
// A string is considered beautiful if it satisfies the following conditions:
//
//
// 	Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
// 	The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
//
//
// For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
//
// Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
// Output: 13
// Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
//
// Constraints:
// 1 <= word.length <= 5 * 105
// 	word consists of characters 'a', 'e', 'i', 'o', and 'u'.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} word
 * @return {number}
 */
var longestBeautifulSubstring = function(word) {
	const vowels = ['a', 'e', 'i', 'o', 'u'];
	let maxLength = 0;
	let currentLength = 0;
	let vowelIndex = 0;

	for (const ch of word) {
		if (ch === vowels[vowelIndex]) {
			currentLength++;
		} else if (vowelIndex < 4 && ch === vowels[vowelIndex + 1]) {
			vowelIndex++;
			currentLength++;
		} else {
			vowelIndex = ch === 'a' ? 0 : -1; // Reset if it's not a valid next vowel
			currentLength = vowelIndex === 0 ? 1 : 0; // Start counting if it's 'a'
		}

		if (vowelIndex === 4) { // All vowels have been seen in order
			maxLength = Math.max(maxLength, currentLength);
		}
	}

	return maxLength;
};
