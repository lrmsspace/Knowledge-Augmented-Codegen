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
public:
    vector<int> pathInZigZagTree(int label) {
        vector<int> path;
        int level = 0;
        int temp = label;
        while (temp > 0) {
            level++;
            temp >>= 1;
        }

        while (label > 0) {
            path.push_back(label);
            int level_start = 1 << (level - 1);
            int level_end = (1 << level) - 1;
            label = level_start + level_end - label;
            label >>= 1;
            level--;
        }

        reverse(path.begin(), path.end());
        return path;            
    }
};
