// Source: https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.
//
//
// 	For example, in the string "(name)is(age)yearsold", there are two bracket pairs that contain the keys "name" and "age".
//
//
// You know the values of a wide range of keys. This is represented by a 2D string array knowledge where each knowledge[i] = [keyi, valuei] indicates that key keyi has a value of valuei.
//
// You are tasked to evaluate all of the bracket pairs. When you evaluate a bracket pair that contains some key keyi, you will:
//
//
// 	Replace keyi and the bracket pair with the key's corresponding valuei.
// 	If you do not know the value of the key, you will replace keyi and the bracket pair with a question mark "?" (without the quotation marks).
//
//
// Each key will appear at most once in your knowledge. There will not be any nested brackets in s.
//
// Return the resulting string after evaluating all of the bracket pairs.
//
// Example:
// Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
// Output: "bobistwoyearsold"
// Explanation:
// The key "name" has a value of "bob", so replace "(name)" with "bob".
// The key "age" has a value of "two", so replace "(age)" with "two".
//
// Constraints:
// 1 <= s.length <= 105
// 	0 <= knowledge.length <= 105
// 	knowledge[i].length == 2
// 	1 <= keyi.length, valuei.length <= 10
// 	s consists of lowercase English letters and round brackets '(' and ')'.
// 	Every open bracket '(' in s will have a corresponding close bracket ')'.
// 	The key in each bracket pair of s will be non-empty.
// 	There will not be any nested bracket pairs in s.
// 	keyi and valuei consist of lowercase English letters.
// 	Each keyi in knowledge is unique.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - Aho-Corasick Algorithm for Pattern Searching (string, trie, aho-corasick, simulation)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns within a larger text efficiently. It's particularly effective for scenarios involving many patterns and potential overlaps.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses it to find all occurrences of these patterns in a text in a single pass. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All patterns in the dictionary are correctly represented in the trie (goto function).; The failure link `f[u]` for any state `u` points to the state representing the longest proper suffix of the string corresponding to `u` that is also a prefix of some pattern.
//   • Tips: Build the trie (goto function) first from all patterns.; Construct failure links using a BFS-like approach to ensure correct shortest suffix matching.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to propagate output matches through failure links can miss valid pattern occurrences.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {string[][]} knowledge
 * @return {string}
 */
var evaluate = function(s, knowledge) {
	const knowledgeMap = new Map();
	for (const [key, value] of knowledge) {
		knowledgeMap.set(key, value);
	}

	let result = '';
	let i = 0;
	while (i < s.length) {
		if (s[i] === '(') {
			let j = i + 1;
			while (j < s.length && s[j] !== ')') {
				j++;
			}
			const key = s.substring(i + 1, j);
			result += knowledgeMap.get(key) || '?';
			i = j + 1; // Move past the closing parenthesis
		} else {
			result += s[i];
			i++;
		}
	}

	return result;
};
