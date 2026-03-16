// Source: https://leetcode.com/problems/cousins-in-binary-tree-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.
//
// Two nodes of a binary tree are cousins if they have the same depth with different parents.
//
// Return the root of the modified tree.
//
// Note that the depth of a node is the number of edges in the path from the root node to it.
//
// Example:
// Input: root = [5,4,9,1,10,null,7]
// Output: [0,0,0,7,7,null,11]
// Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
// - Node with value 5 does not have any cousins so its sum is 0.
// - Node with value 4 does not have any cousins so its sum is 0.
// - Node with value 9 does not have any cousins so its sum is 0.
// - Node with value 1 has a cousin with value 7 so its sum is 7.
// - Node with value 10 has a cousin with value 7 so its sum is 7.
// - Node with value 7 has cousins with values 1 and 10 so its sum is 11.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 104
//

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public TreeNode replaceValueInTree(TreeNode root) {
        if (root == null) {
            return null;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int size = queue.size();
            int levelSum = 0;
            List<TreeNode> currentLevelNodes = new ArrayList<>();

            for (int i = 0; i < size; i++) {
                TreeNode currentNode = queue.poll();
                currentLevelNodes.add(currentNode);
                levelSum += currentNode.val;

                if (currentNode.left != null) {
                    queue.offer(currentNode.left);
                }
                if (currentNode.right != null) {
                    queue.offer(currentNode.right);
                }
            }

            for (TreeNode node : currentLevelNodes) {
                int childrenSum = 0;
                if (node.left != null) {
                    childrenSum += node.left.val;
                }
                if (node.right != null) {
                    childrenSum += node.right.val;
                }

                if (node.left != null) {
                    node.left.val = levelSum - childrenSum;
                }
                if (node.right != null) {
                    node.right.val = levelSum - childrenSum;
                }
            }
        }

        root.val = 0; // Root has no cousins
        return root;            
    }
}
