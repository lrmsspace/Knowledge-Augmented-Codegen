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

/**
 * @param {number} label
 * @return {number[]}
 */
var pathInZigZagTree = function(label) {
    const path = [];
    let level = Math.floor(Math.log2(label)) + 1;
    while (level > 0) {
        path.push(label);
        const levelStart = 2 ** (level - 1);
        const levelEnd = 2 ** level - 1;
        label = Math.floor((levelStart + levelEnd - label) / 2);
        level--;
    }
    return path.reverse();
        
};
