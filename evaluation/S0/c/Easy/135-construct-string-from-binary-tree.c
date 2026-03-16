// Source: https://leetcode.com/problems/construct-string-from-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root node of a binary tree, your task is to create a string representation of the tree following a specific set of formatting rules. The representation should be based on a preorder traversal of the binary tree and must adhere to the following guidelines:
//
//
// 	
// 	Node Representation: Each node in the tree should be represented by its integer value.
// 	
// 	
// 	Parentheses for Children: If a node has at least one child (either left or right), its children should be represented inside parentheses. Specifically:
//
// 	
// 		If a node has a left child, the value of the left child should be enclosed in parentheses immediately following the node's value.
// 		If a node has a right child, the value of the right child should also be enclosed in parentheses. The parentheses for the right child should follow those of the left child.
// 	
// 	
// 	
// 	Omitting Empty Parentheses: Any empty parentheses pairs (i.e., ()) should be omitted from the final string representation of the tree, with one specific exception: when a node has a right child but no left child. In such cases, you must include an empty pair of parentheses to indicate the absence of the left child. This ensures that the one-to-one mapping between the string representation and the original binary tree structure is maintained.
//
// 	In summary, empty parentheses pairs should be omitted when a node has only a left child or no children. However, when a node has a right child but no left child, an empty pair of parentheses must precede the representation of the right child to reflect the tree's structure accurately.
//
// Example:
// Input: root = [1,2,3,4]
// Output: "1(2(4))(3)"
// Explanation: Originally, it needs to be "1(2(4)())(3()())", but you need to omit all the empty parenthesis pairs. And it will be "1(2(4))(3)".
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-1000 <= Node.val <= 1000
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
char* tree2str(struct TreeNode* root) {
    if (!root) return "";

    // Allocate a buffer for the result string
    // Assuming a maximum of 12 characters per node (including parentheses and sign)
    // and a maximum of 10^4 nodes, we allocate a buffer of size 120000.
    char* result = (char*)malloc(120000 * sizeof(char));
    result[0] = '\0'; // Initialize the string

    // Helper function to perform preorder traversal and build the string
    void buildString(struct TreeNode* node, char* str) {
        if (!node) return;

        // Append the current node's value
        char buffer[12];
        sprintf(buffer, "%d", node->val);
        strcat(str, buffer);

        // If there is a left child or right child, we need to add parentheses
        if (node->left || node->right) {
            // Process left child
            strcat(str, "(");
            if (node->left) {
                buildString(node->left, str);
            }
            strcat(str, ")");

            // Process right child
            if (node->right) {
                strcat(str, "(");
                buildString(node->right, str);
                strcat(str, ")");
            }
        }
    }

    buildString(root, result);
    return result;      
}
