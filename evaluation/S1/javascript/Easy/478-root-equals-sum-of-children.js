// Source: https://leetcode.com/problems/root-equals-sum-of-children/   |   Difficulty: Easy
//
// Problem Description:
// You are given the root of a binary tree that consists of exactly 3 nodes: the root, its left child, and its right child.
//
// Return true if the value of the root is equal to the sum of the values of its two children, or false otherwise.
//
// Example:
// Input: root = [10,4,6]
// Output: true
// Explanation: The values of the root, its left child, and its right child are 10, 4, and 6, respectively.
// 10 is equal to 4 + 6, so we return true.
//
// Constraints:
// The tree consists only of the root, its left child, and its right child.
// 	-100 <= Node.val <= 100
//
// Helpful references (internal KB):
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use this when representing positive rational numbers as unique paths in a binary tree or when efficiently approximating irrational numbers. It's ideal for finding a fraction's path or its position within ordered sequences.
//   • Idea: The Stern-Brocot tree uniquely maps every positive rational number to a binary path, constructed by repeatedly taking mediants. This allows for efficient search and representation of fractions with O(log(p+q)) time complexity.
//   • Invariants: The target fraction p/q always lies strictly between the current left boundary pL/qL and right boundary pR/qR.; The current left and right boundary fractions (pL/qL, pR/qR) are always adjacent terms in some Farey sequence.
//   • Tips: Initialize search boundaries with 0/1 and 1/0 (or 1/1 for positive fractions).; Calculate the mediant (pL+pR)/(qL+qR) to determine the next candidate fraction.
//   • Pitfalls: Naive O(p+q) search without run-length encoding can be too slow for large fractions.; Incorrectly handling initial boundary conditions (e.g., 0/1, 1/0, 1/1).
// - Randomized Heap (heap, tree, randomized, recursion)
//   • When to use: Use when needing a heap with efficient merge operations and guaranteed expected logarithmic time for all standard operations, including arbitrary element removal.
//   • Idea: A randomized heap is a binary tree-based heap that uses randomization to maintain heap properties, ensuring all operations like insertion, deletion, and merging run in expected O(log n) time.
//   • Invariants: The root node always contains the minimum (or maximum) element.; Every node's value is less than or equal to (or greater than or equal to) its children's values.
//   • Tips: Randomization simplifies implementation compared to other mergeable heaps.; Expected time complexity is generally sufficient for practical purposes.
//   • Pitfalls: Worst-case time complexity can be higher, though rare.; Relies on a good random number generator.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {boolean}
 */
var checkTree = function(root) {
    return root.val === root.left.val + root.right.val; 
};
