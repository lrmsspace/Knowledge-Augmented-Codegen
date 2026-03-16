// Source: https://leetcode.com/problems/removing-stars-from-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, which contains stars *.
//
// In one operation, you can:
//
//
// 	Choose a star in s.
// 	Remove the closest non-star character to its left, as well as remove the star itself.
//
//
// Return the string after all stars have been removed.
//
// Note:
//
//
// 	The input will be generated such that the operation is always possible.
// 	It can be shown that the resulting string will always be unique.
//
// Example:
// Input: s = "leet**cod*e"
// Output: "lecoe"
// Explanation: Performing the removals from left to right:
// - The closest character to the 1st star is 't' in "leet**cod*e". s becomes "lee*cod*e".
// - The closest character to the 2nd star is 'e' in "lee*cod*e". s becomes "lecod*e".
// - The closest character to the 3rd star is 'd' in "lecod*e". s becomes "lecoe".
// There are no more stars, so we return "lecoe".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters and stars *.
// 	The operation above can be performed on s.
//
// Helpful references (internal KB):
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var removeStars = function(s) {
  const result = [];
  for (const char of s) {
    if (char === '*') {
      result.pop();
    } else {
      result.push(char);
    }
  }
  return result.join('');
};
