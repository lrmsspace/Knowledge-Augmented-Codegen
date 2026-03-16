// Source: https://leetcode.com/problems/count-complete-tree-nodes/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a complete binary tree, return the number of the nodes in the tree.
//
// According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
//
// Design an algorithm that runs in less than O(n) time complexity.
//
// Example:
// Input: root = [1,2,3,4,5,6]
// Output: 6
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5 * 104].
// 	0 <= Node.val <= 5 * 104
// 	The tree is guaranteed to be complete.
//
// Helpful references (internal KB):
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
// - Sqrt Tree (array, tree, recursion, simulation)
//   • When to use: Use for efficient range queries on an array, achieving very low query complexity by leveraging a hierarchical block decomposition and specific structural properties like power-of-two block sizes.
//   • Idea: A Sqrt Tree is a hierarchical data structure designed for answering range queries on an array, achieving O(log log n) or better query time by recursively decomposing the array into blocks and layers.
//   • Invariants: Each layer of the Sqrt Tree consists of segments of equal length.; All blocks within a given layer have an equal, power-of-two size.
//   • Tips: Pad the input array with dummy elements to ensure its size is a power of two for simplified block calculations.; Ensure all block sizes on each layer are powers of two to enable efficient binary representation tricks for queries.
//   • Pitfalls: Incorrectly calculating block boundaries or segment sizes, leading to off-by-one errors or out-of-bounds access.; Overlooking the memory overhead associated with storing precomputed values for all blocks across multiple layers.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int left_depth = 0;
    struct TreeNode* left_node = root;
    while (left_node != NULL) {
        left_depth++;
        left_node = left_node->left;
    }

    int right_depth = 0;
    struct TreeNode* right_node = root;
    while (right_node != NULL) {
        right_depth++;
        right_node = right_node->right;
    }

    if (left_depth == right_depth) {
        return (1 << left_depth) - 1; // 2^depth - 1
    } else {
        return 1 + countNodes(root->left) + countNodes(root->right);
    }       
}
