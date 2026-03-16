// Source: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree
//
//
// struct Node {
//   int val;
//   Node *left;
//   Node *right;
//   Node *next;
// }
//
//
// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
//
// Initially, all next pointers are set to NULL.
//
// Example:
// Input: root = [1,2,3,4,5,null,7]
// Output: [1,#,2,3,#,4,5,7,#]
// Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.
//
// Constraints:
// The number of nodes in the tree is in the range [0, 6000].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow-up:
//
//
// 	You may only use constant extra space.
// 	The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem.
//

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;

        Node* current = root;
        Node* nextLevelHead = nullptr; // Head of the next level
        Node* prev = nullptr; // The previous node on the next level

        while (current) {
            while (current) {
                if (current->left) {
                    if (prev) {
                        prev->next = current->left;
                    } else {
                        nextLevelHead = current->left;
                    }
                    prev = current->left;
                }
                if (current->right) {
                    if (prev) {
                        prev->next = current->right;
                    } else {
                        nextLevelHead = current->right;
                    }
                    prev = current->right;
                }
                current = current->next;
            }
            current = nextLevelHead;
            nextLevelHead = nullptr;
            prev = nullptr;
        }

        return root;            
    }
};
