// Source: https://leetcode.com/problems/decoded-string-at-index/   |   Difficulty: Medium
//
// Problem Description:
// You are given an encoded string s. To decode the string to a tape, the encoded string is read one character at a time and the following steps are taken:
//
//
// 	If the character read is a letter, that letter is written onto the tape.
// 	If the character read is a digit d, the entire current tape is repeatedly written d - 1 more times in total.
//
//
// Given an integer k, return the kth letter (1-indexed) in the decoded string.
//
// Example:
// Input: s = "leet2code3", k = 10
// Output: "o"
// Explanation: The decoded string is "leetleetcodeleetleetcodeleetleetcode".
// The 10th letter in the string is "o".
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists of lowercase English letters and digits 2 through 9.
// 	s starts with a letter.
// 	1 <= k <= 109
// 	It is guaranteed that k is less than or equal to the length of the decoded string.
// 	The decoded string is guaranteed to have less than 263 letters.
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
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
 * @return {string}
 */
var decodeAtIndex = function(s, k) {
	let size = 0;

	// Calculate the size of the decoded string until it reaches or exceeds k
	for (const char of s) {
		if (isNaN(char)) {
			size += 1; // For letters, increment size by 1
		} else {
			size *= parseInt(char); // For digits, multiply the current size by the digit
		}

		if (size >= k) break; // Stop if we've reached or exceeded k
	}

	// Traverse the encoded string in reverse to find the k-th character
	for (let i = s.length - 1; i >= 0; i--) {
		const char = s[i];
		if (isNaN(char)) {
			if (k % size === 0) return char; // If k is a multiple of size, return the current character
			size -= 1; // Decrement size for letters
		} else {
			size /= parseInt(char); // Divide size by the digit for digits
			k %= size; // Update k to find the position within the repeated section
		}
	}

	return ''; // This line should never be reached due to problem constraints
};
