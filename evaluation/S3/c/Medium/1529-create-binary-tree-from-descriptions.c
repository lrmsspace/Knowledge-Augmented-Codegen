// Source: https://leetcode.com/problems/create-binary-tree-from-descriptions/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,
//
//
// 	If isLefti == 1, then childi is the left child of parenti.
// 	If isLefti == 0, then childi is the right child of parenti.
//
//
// Construct the binary tree described by descriptions and return its root.
//
// The test cases will be generated such that the binary tree is valid.
//
// Example:
// Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
// Output: [50,20,80,15,17,19]
// Explanation: The root node is the node with value 50 since it has no parent.
// The resulting binary tree is shown in the diagram.
//
// Constraints:
// 1 <= descriptions.length <= 104
// 	descriptions[i].length == 3
// 	1 <= parenti, childi <= 105
// 	0 <= isLefti <= 1
// 	The binary tree described by descriptions is valid.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
struct TreeNode* createBinaryTree(int** descriptions, int descriptionsSize, int* descriptionsColSize) {
   
    // Step 1: Create a mapping of parent to its children and track all nodes
    typedef struct NodeInfo {
        int value;
        struct TreeNode* node;
        int hasParent; // Flag to identify the root node later
    } NodeInfo;

    NodeInfo nodeMap[100001] = {0}; // Assuming values are in the range [1, 100000]
    
    for (int i = 0; i < descriptionsSize; i++) {
        int parentVal = descriptions[i][0];
        int childVal = descriptions[i][1];
        int isLeft = descriptions[i][2];

        // Ensure parent node exists in the map
        if (nodeMap[parentVal].node == NULL) {
            nodeMap[parentVal].value = parentVal;
            nodeMap[parentVal].node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            nodeMap[parentVal].node->val = parentVal;
            nodeMap[parentVal].node->left = NULL;
            nodeMap[parentVal].node->right = NULL;
        }

        // Ensure child node exists in the map
        if (nodeMap[childVal].node == NULL) {
            nodeMap[childVal].value = childVal;
            nodeMap[childVal].node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            nodeMap[childVal].node->val = childVal;
            nodeMap[childVal].node->left = NULL;
            nodeMap[childVal].node->right = NULL;
        }

        // Link parent and child nodes
        if (isLeft) {
            nodeMap[parentVal].node->left = nodeMap[childVal].node;
        } else {
            nodeMap[parentVal].node->right = nodeMap[childVal].node;
        }

        // Mark the child as having a parent
        nodeMap[childVal].hasParent = 1;
    }

    // Step 2: Find the root node (the one that does not have a parent)
    struct TreeNode* root = NULL;
    for (int i = 1; i <= 100000; i++) {
        if (nodeMap[i].node != NULL && !nodeMap[i].hasParent) {
            root = nodeMap[i].node;
            break;
        }
    }

    return root;
}
