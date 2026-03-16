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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* createBinaryTree(int** descriptions, int descriptionsSize, int* descriptionsColSize) {
    #define MAX_NODES 100005
    struct TreeNode* nodes[MAX_NODES];
    int has_parent[MAX_NODES] = {0};
    
    for (int i = 0; i < descriptionsSize; i++) {
        int parent_val = descriptions[i][0];
        int child_val = descriptions[i][1];
        int is_left = descriptions[i][2];
        
        if (nodes[parent_val] == NULL) {
            nodes[parent_val] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            nodes[parent_val]->val = parent_val;
            nodes[parent_val]->left = NULL;
            nodes[parent_val]->right = NULL;
        }
        
        if (nodes[child_val] == NULL) {
            nodes[child_val] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            nodes[child_val]->val = child_val;
            nodes[child_val]->left = NULL;
            nodes[child_val]->right = NULL;
        }
        
        if (is_left) {
            nodes[parent_val]->left = nodes[child_val];
        } else {
            nodes[parent_val]->right = nodes[child_val];
        }
        
        has_parent[child_val] = 1;
    }
    
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes[i] != NULL && has_parent[i] == 0) {
            return nodes[i];
        }
    }
    
    return NULL;        
}
