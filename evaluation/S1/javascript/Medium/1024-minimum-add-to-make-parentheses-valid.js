// Source: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/   |   Difficulty: Medium
//
// Problem Description:
// A parentheses string is valid if and only if:
//
//
// 	It is the empty string,
// 	It can be written as AB (A concatenated with B), where A and B are valid strings, or
// 	It can be written as (A), where A is a valid string.
//
//
// You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.
//
//
// 	For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
//
//
// Return the minimum number of moves required to make s valid.
//
// Example:
// Input: s = "())"
// Output: 1
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '(' or ')'.
//
// Helpful references (internal KB):
// - Balanced bracket sequences (number, counting)
//   • When to use: Use when the problem asks for the total number of valid arrangements of opening and closing brackets, ensuring all pairs are matched and correctly nested. It applies to combinatorial problems requiring structured pairing.
//   • Idea: This technique counts the number of ways to form sequences of opening and closing brackets such that they are balanced and properly nested. It is a classic combinatorial problem, typically solved in O(N) or O(N^2) time.
//   • Invariants: At any point in sequence construction, the count of open brackets placed must be greater than or equal to the count of closed brackets placed.; The total number of open brackets in a complete valid sequence must exactly equal the total number of closed brackets.
//   • Tips: Recognize the connection to Catalan numbers for common variations (e.g., N pairs of parentheses).; Dynamic programming can solve more complex variations with different bracket types or constraints.
//   • Pitfalls: Forgetting the 'prefix sum' condition: the count of open brackets must always be greater than or equal to close brackets at any point.; Incorrectly applying Catalan numbers to problems with additional constraints or different bracket types.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
 * @return {number}
 */
var minAddToMakeValid = function(s) {
	let balance = 0;
	let insertions = 0;

	for (const char of s) {
		if (char === '(') {
			balance++;
		} else {
			if (balance > 0) {
				balance--;
			} else {
				insertions++;
			}
		}
	}

	return insertions + balance;
};
