// Source: https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// In an infinite binary tree where every node has two children, the nodes are labelled in row order.
//
// In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.
//
//
//
// Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.
//
// Example:
// Input: label = 14
// Output: [1,3,4,14]
//
// Constraints:
// 1 <= label <= 10^6
//
// Helpful references (internal KB):
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use this when representing positive rational numbers as unique paths in a binary tree or when efficiently approximating irrational numbers. It's ideal for finding a fraction's path or its position within ordered sequences.
//   • Idea: The Stern-Brocot tree uniquely maps every positive rational number to a binary path, constructed by repeatedly taking mediants. This allows for efficient search and representation of fractions with O(log(p+q)) time complexity.
//   • Invariants: The target fraction p/q always lies strictly between the current left boundary pL/qL and right boundary pR/qR.; The current left and right boundary fractions (pL/qL, pR/qR) are always adjacent terms in some Farey sequence.
//   • Tips: Initialize search boundaries with 0/1 and 1/0 (or 1/1 for positive fractions).; Calculate the mediant (pL+pR)/(qL+qR) to determine the next candidate fraction.
//   • Pitfalls: Naive O(p+q) search without run-length encoding can be too slow for large fractions.; Incorrectly handling initial boundary conditions (e.g., 0/1, 1/0, 1/1).
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pathInZigZagTree(int label, int* returnSize) {
    int level = 0, temp = label;
    while (temp > 0) {
        temp /= 2;
        level++;
    }
    
    int* path = (int*)malloc(level * sizeof(int));
    *returnSize = level;
    
    for (int i = level - 1; i >= 0; i--) {
        path[i] = label;
        int levelStart = 1 << i; // 2^i
        int levelEnd = (1 << (i + 1)) - 1; // 2^(i+1) - 1
        if (i % 2 == 0) { // Odd level (0-based index)
            label = (levelStart + levelEnd - label) / 2;
        } else { // Even level
            label /= 2;
        }
    }
    
    return path;        
}
