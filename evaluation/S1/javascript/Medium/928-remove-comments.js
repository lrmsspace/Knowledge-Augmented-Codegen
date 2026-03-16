// Source: https://leetcode.com/problems/remove-comments/   |   Difficulty: Medium
//
// Problem Description:
// Given a C++ program, remove comments from it. The program source is an array of strings source where source[i] is the ith line of the source code. This represents the result of splitting the original source code string by the newline character '\n'.
//
// In C++, there are two types of comments, line comments, and block comments.
//
//
// 	The string "//" denotes a line comment, which represents that it and the rest of the characters to the right of it in the same line should be ignored.
// 	The string "/*" denotes a block comment, which represents that all characters until the next (non-overlapping) occurrence of "*/" should be ignored. (Here, occurrences happen in reading order: line by line from left to right.) To be clear, the string "/*/" does not yet end the block comment, as the ending would be overlapping the beginning.
//
//
// The first effective comment takes precedence over others.
//
//
// 	For example, if the string "//" occurs in a block comment, it is ignored.
// 	Similarly, if the string "/*" occurs in a line or block comment, it is also ignored.
//
//
// If a certain line of code is empty after removing comments, you must not output that line: each string in the answer list will be non-empty.
//
// There will be no control characters, single quote, or double quote characters.
//
//
// 	For example, source = "string s = "/* Not a comment. */";" will not be a test case.
//
//
// Also, nothing else such as defines or macros will interfere with the comments.
//
// It is guaranteed that every open block comment will eventually be closed, so "/*" outside of a line or block comment always starts a new comment.
//
// Finally, implicit newline characters can be deleted by block comments. Please see the examples below for details.
//
// After removing the comments from the source code, return the source code in the same format.
//
// Example:
// Input: source = ["/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"]
// Output: ["int main()","{ ","  ","int a, b, c;","a = b + c;","}"]
// Explanation: The line by line code is visualized as below:
// /*Test program */
// int main()
// { 
//   // variable declaration 
// int a, b, c;
// /* This is a test
//    multiline  
//    comment for 
//    testing */
// a = b + c;
// }
// The string /* denotes a block comment, including line 1 and lines 6-9. The string // denotes line 4 as comments.
// The line by line output code is visualized as below:
// int main()
// { 
//   
// int a, b, c;
// a = b + c;
// }
//
// Constraints:
// 1 <= source.length <= 100
// 	0 <= source[i].length <= 80
// 	source[i] consists of printable ASCII characters.
// 	Every open block comment is eventually closed.
// 	There are no single-quote or double-quote in the input.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} source
 * @return {string[]}
 */
var removeComments = function(source) {
	// We can iterate through each line of the source code and use a flag to track whether we are currently inside a block comment. 
	// When we encounter the start of a block comment (i.e., "/*"), we set the flag to true, and when we encounter the end of a block comment (i.e., "*/"), we set the flag to false. 
	// For line comments (i.e., "//"), we can ignore the rest of the line after encountering it. 
	// We can build the resulting lines of code in an array and return it at the end.
	const result = [];
	let inBlockComment = false;
	let newLine = '';

	for (const line of source) {
		let i = 0;
		while (i < line.length) {
			if (!inBlockComment && i + 1 < line.length && line[i] === '/' && line[i + 1] === '*') {
				inBlockComment = true;
				i += 2; // Skip "/*"
			} else if (inBlockComment && i + 1 < line.length && line[i] === '*' && line[i + 1] === '/') {
				inBlockComment = false;
				i += 2; // Skip "*/"
			} else if (!inBlockComment && i + 1 < line.length && line[i] === '/' && line[i + 1] === '/') {
				break; // Ignore the rest of the line
			} else if (!inBlockComment) {
				newLine += line[i]; // Add character to newLine if not in block comment
				i++;
			} else {
				i++; // Skip characters inside block comment
			}
		}

		if (!inBlockComment && newLine.length > 0) {
			result.push(newLine); // Add non-empty lines to result
			newLine = ''; // Reset newLine for the next iteration
		}
	}

	return result;
};
