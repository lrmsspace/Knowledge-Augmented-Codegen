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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pathInZigZagTree(int label, int* returnSize) {
    int level = 0, temp = label;
    while (temp) {
        level++;
        temp >>= 1;
    }

    int* path = (int*)malloc(level * sizeof(int));
    *returnSize = level;

    for (int i = level - 1; i >= 0; i--) {
        path[i] = label;
        int level_start = 1 << (level - 1);
        int level_end = (1 << level) - 1;
        label = level_start + level_end - label;
        label >>= 1;
        level--;
    }

    return path;        
}
