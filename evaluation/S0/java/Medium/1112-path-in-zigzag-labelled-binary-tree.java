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

class Solution {
    public List<Integer> pathInZigZagTree(int label) {
        List<Integer> path = new ArrayList<>();
        int level = (int) (Math.log(label) / Math.log(2));
        
        while (label > 0) {
            path.add(label);
            int levelStart = 1 << level; // 2^level
            int levelEnd = (1 << (level + 1)) - 1; // 2^(level+1) - 1
            
            // Calculate the label of the parent in a normal binary tree
            label = levelStart + levelEnd - label; // Find the mirrored label
            label /= 2; // Move to the parent
            level--;
        }
        
        Collections.reverse(path);
        return path;            
    }
}
