// Source: https://leetcode.com/problems/n-ary-tree-preorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of an n-ary tree, return the preorder traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)
//
// Example:
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [1,3,5,6,2,4]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	0 <= Node.val <= 104
// 	The height of the n-ary tree is less than or equal to 1000.
//
//
//  
// Follow up: Recursive solution is trivial, could you do it iteratively?
//

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> result;
        preorderHelper(root, result);
        return result;          
    }
};
